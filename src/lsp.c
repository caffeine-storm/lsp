#include <expr.h>
#include <lsp_assert.h>
#include <printer.h>
#include <reader.h>
#include <stack.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum EVAL_RESULT {
	EVAL_PUSH_EXPR,
	EVAL_EXIT,
	EVAL_ERROR
};

void print_prompt( FILE * out ) {
	fprintf( out, "> " );
}

int eval( stack_type * stack, expr_type * expr ) {
	// TODO: implement eval :p
	(void) stack;
	(void) expr;
	return EVAL_EXIT;
}

int main( int argc, char * * argv ) {
	(void) argc;
	(void) argv;

	stack_type stack;
	stack_init( &stack );

	reader_type reader;
	reader_init( &reader );

	printer_type printer;

	while( 1 ) {
		print_prompt( stdout );

		expr_type expr;
		expr_init( &expr );

		int ret = reader_read( &reader, stdin, &expr );
		switch( ret ) {
			case read_result_fail:
				printf( "read-failure: <TODO: descriptive error message>\n" );
				continue;
			case read_result_fatal:
				printf( "fatal read failure: <TODO: debug info from reader>\n" );
				exit( 1 );
			case read_result_ok:
				;
		}

		ret = eval( &stack, &expr );
		switch( ret ) {
			case EVAL_PUSH_EXPR: {
				stack_push( &stack, &expr );
				break;
			}
			case EVAL_EXIT: {
				expr_denit( &expr );

				printf( "Goodbye!\n" );

				expr_type * temp = stack_top( &stack );
				LSP_ASSERT( temp->type_code == EXPR_TYPE_INT, "exit requires an int!" );
				int return_code = expr_get_int( temp );

				exit( return_code );
			}
			case EVAL_ERROR: {
				// TODO: print an error message that eval will push on the stack
				continue;
			}
			default: {
				assert( 0 && "Invalid eval result (eval internal error)" );
				exit( 1 );
			}
		}

		expr_type * top = stack_top( &stack );
		printer_print( &printer, top, stdout );
	}

    return 0;
}

