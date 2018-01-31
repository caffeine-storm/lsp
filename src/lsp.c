#include <expr.h>
#include <lsp_assert.h>
#include <lsp_print.h>
#include <lsp_util.h>
#include <namespace.h>
#include <printer.h>
#include <reader.h>
#include <stack.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum EVAL_RESULT {
	EVAL_PUSH_EXPR,
	EVAL_CONTINUE,
	EVAL_EXIT,
	EVAL_ERROR
};

int status_to_rc( int s ) {
	switch( s ) {
		case EVAL_PUSH_EXPR:
		case EVAL_CONTINUE:
		case EVAL_EXIT:
			return 0;
		case EVAL_ERROR:
			return 1;
		default:
			LSP_ABORT( "snh" );
	}
}

void print_prompt( FILE * out ) {
	fprintf( out, "> " );
}

void stdout_prompt() {
	print_prompt( stdout );
}

int eval( stack_type * stack, namespace_type * ns, expr_type * expr ) {
	(void) stack;
	switch( expr->type_code ) {
		case EXPR_TYPE_EOF:
			TRACE( "eval: eof-expr" );
			return EVAL_EXIT;
		case EXPR_TYPE_SYMBOL: {
			TRACE( "eval: symbol-expr" );
			callable_type entry = namespace_get_symbol( ns, expr_get_symbol( expr ) );
			if( !entry ) {
				printf( "symbol lookup failure for '%s'\n", expr->val.symbol );
				return EVAL_ERROR;
			}
			(*entry)( stack );
			return EVAL_CONTINUE;
		}
		case EXPR_TYPE_INT:
		case EXPR_TYPE_STRING:
			break;
		default: {
			TRACE( "eval: unhandled-expr" );
			LSP_ABORT( "snh" );
		}
	}

	return EVAL_PUSH_EXPR;
}

int main( int argc, char * * argv ) {
	(void) argc;
	(void) argv;

	int ret;
	int last_status = EVAL_CONTINUE;

	printer_type printer;

	stack_type stack;
	stack_init( &stack );

	void print_fn( stack_type * s ) {
		if( stack_size( s ) < 1 ) {
			fprintf( stderr, "error: stack underflow\n" );
			return;
		}
		expr_type * e = stack_top( s );
		printer_print( &printer, e, stdout );
		stack_pop( s );
		kill_expr( e );
	}

	void print_stack( stack_type * s ) {
		size_t sz = stack_size( s );
		if( sz == 0 ) {
			expr_type * e = make_expr();
			char * s = strdup( "<empty stack>" );
			expr_set_symbol( e, s );
			printer_print( &printer, e, stdout );
			kill_expr( e );
			return;
		}
		while( sz-- ) {
			expr_type * e = stack_at( s, sz );
			printer_print( &printer, e, stdout );
		}
	}

	void exit_fn( stack_type * s ) {
		if( stack_size( s ) < 1 ) {
			fprintf( stderr, "error: stack underflow\n" );
			return;
		}

		expr_type * e = stack_top( s );
		if( e->type_code != EXPR_TYPE_INT ) {
			fprintf( stderr, "error: can't apply 'exit' to non-int\n" );
			return;
		}

		exit( expr_get_int( e ) );
	}

	namespace_type ns;
	namespace_init( &ns );

	namespace_bind( &ns, ".", print_fn );
	namespace_bind( &ns, ".s", print_stack );
	namespace_bind( &ns, "exit", exit_fn );

	reader_type reader;
	ret = reader_init( &reader, stdin );

	while( 1 ) {
		expr_type * expr = malloc( sizeof( expr_type ) );
		expr_init( expr );

		TRACE( "going to read next" );
		ret = reader_read_next( &reader, expr, &stdout_prompt );
		TRACE( "read returned %d", ret );
		switch( ret ) {
			case read_result_fail:
				printf( "read-failure: <TODO: descriptive error message>\n" );
				expr_denit( expr );
				free( expr );
				continue;
			case read_result_fatal:
				printf( "fatal read failure: <TODO: debug info from reader>\n" );
				exit( 1 );
			case read_result_ok:
				;
		}

		ret = eval( &stack, &ns, expr );
		switch( ret ) {
			case EVAL_PUSH_EXPR: {
				stack_push( &stack, expr );
				break;
			}
			case EVAL_CONTINUE: {
				expr_denit( expr );
				free( expr );
				break;
			}
			case EVAL_EXIT: {
				expr_denit( expr );
				free( expr );

				printf( "Goodbye!\n" );
				exit( status_to_rc( last_status ) );
			}
			case EVAL_ERROR: {
				// TODO: print an error message that eval will push on the stack
				printf( "ERROR\n" );
				break;
			}
			default: {
				assert( 0 && "Invalid eval result (eval internal error)" );
				exit( 1 );
			}
		}

		last_status = ret;
	}

	return 0;
}

