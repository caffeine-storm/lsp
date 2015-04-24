#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSP_ABORT( msg ) do { \
	lsp_abort( __FILE__, __LINE__, msg ); \
} while( 0 )

#define LSP_ASSERT( cond, msg ) do { \
	if( !cond ) { \
		lsp_abort( __FILE__, __LINE__, msg ); \
	} \
} while( 0 )

void lsp_abort( char const * const filename, int lineno, char const * msg ) {
	printf( "LSP-ABORT: %s:%d: %s\n", filename, lineno, msg );
	exit( 2 );
}

enum EVAL_RESULT {
	EVAL_PUSH_SEXPR,
	EVAL_EXIT,
	EVAL_ERROR
};

enum READ_RESULT {
	READ_SUCCESS,
	READ_FAILURE
};

enum EXPR_TYPE {
	EXPR_TYPE_NIL,
	EXPR_TYPE_SYMBOL,
	EXPR_TYPE_CONS,
	EXPR_TYPE_INT
};

typedef struct {
	int type_code;
	union {
		int int_val;
		char * symbol;
	} val;
} sexpr_type;

void sexpr_init( sexpr_type * expr ) {
	expr->type_code = EXPR_TYPE_NIL;
	memset( &expr->val, 0, sizeof( expr->val ) );
}

void sexpr_denit( sexpr_type * expr ) {
	switch( expr->type_code ) {
		case EXPR_TYPE_SYMBOL: {
			free( expr->val.symbol );
			return;
		}
		case EXPR_TYPE_NIL:
		case EXPR_TYPE_INT:
			// no-op
			;
	}
}

int sexpr_get_int( sexpr_type * expr ) {
	LSP_ASSERT( expr->type_code == EXPR_TYPE_INT, "Can only get int value from a int expression!" );
	return expr->val.int_val;
}

void sexpr_set_int( sexpr_type * expr, int val ) {
	sexpr_denit( expr );
	expr->type_code = EXPR_TYPE_INT;
	expr->val.int_val = val;
}

char * sexpr_get_symbol( sexpr_type * expr ) {
	LSP_ASSERT( expr->type_code == EXPR_TYPE_SYMBOL, "Can only get symbol value from a symbol expression!" );
	return expr->val.symbol;
}

typedef struct stack_item_struct {
	sexpr_type * val;
	struct stack_item_struct * prev;
} stack_item_type;

void stack_item_init( stack_item_type * item, sexpr_type * val, stack_item_type * prev ) {
	item->val = val;
	item->prev = prev;
}

void stack_item_denit( stack_item_type * item ) {
	sexpr_denit( item->val );
	item->prev = NULL;
}

typedef struct {
	stack_item_type * top;
	size_t size;
} stack_type;

int stack_push( stack_type * stack, sexpr_type * expr );
void stack_init( stack_type * stack ) {
	sexpr_type * canary = malloc( sizeof( sexpr_type ) );
	sexpr_init( canary );
	sexpr_set_int( canary, 0 );
	stack->size = 0;
	stack_push( stack, canary );
}

// TODO: warn about ignored return value
int stack_push( stack_type * stack, sexpr_type * expr ) {
	stack_item_type * old_top = stack->top;
	stack_item_type * new_top = malloc( sizeof( stack_item_type ) );

	if( !new_top ) {
		return 1;
	}

	stack_item_init( new_top, expr, old_top );
	stack->top = new_top;
	++stack->size;
	return 0;
}

sexpr_type * stack_top( stack_type * stack ) {
	return stack->top->val;
}

void stack_pop( stack_type * stack ) {
	if( stack->size == 0 ) {
		LSP_ABORT( "Can't pop empty stack!" );
	}
	stack_item_type * old_top = stack->top;
	stack->top = old_top->prev;
	stack->size--;
	stack_item_denit( old_top );
}

int read_sexpr( FILE * in, sexpr_type * result ) {
	// TODO: implement read :p
	return 0;
}

void print_prompt( FILE * out ) {
	fprintf( out, "> " );
}

int eval( stack_type * stack, sexpr_type * expr ) {
	// TODO: implement eval :p
	return EVAL_EXIT;
}

void sexpr_print( sexpr_type * expr, FILE * out ) {
	switch( expr->type_code ) {
		case EXPR_TYPE_NIL: {
			fprintf( out, "n" );
			return;
		}
		case EXPR_TYPE_SYMBOL: {
			// For now, the only symbol is 'exit'
			assert( strcmp( sexpr_get_symbol( expr ), "exit" ) == 0 );
			fprintf( out, "exit" );
			return;
		}
		case EXPR_TYPE_INT: {
			fprintf( out, "%d", sexpr_get_int( expr )  );
			return;
		}
		case EXPR_TYPE_CONS: {
			// TODO: print-list... until then, fall through to failure.
		}
		default: {
			// fall-through
		}
	}
	LSP_ABORT( "Unknown expr type" );
}

int main( int argc, char * * argv ) {
	stack_type stack;
	stack_init( &stack );
	
	while( 1 ) {
		print_prompt( stdout );

		sexpr_type expr;
		sexpr_init( &expr );
		int ret = read_sexpr( stdin, &expr );
		switch( ret ) {
			case READ_SUCCESS:
				break;
			case READ_FAILURE:
				printf( "read-failure: <TODO: descriptive error message>\n" );
				continue;
		}

		ret = eval( &stack, &expr );
		switch( ret ) {
			case EVAL_PUSH_SEXPR: {
				stack_push( &stack, &expr );
				break;
			}
			case EVAL_EXIT: {
				sexpr_denit( &expr );

				printf( "Goodbye!\n" );

				sexpr_type * temp = stack_top( &stack );
				LSP_ASSERT( temp->type_code == EXPR_TYPE_INT, "exit requires an int!" );
				int return_code = sexpr_get_int( temp );

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

		sexpr_type * temp = stack_top( &stack );
		sexpr_print( temp, stdout );
	}
    printf( "Hello World!\n" );
    return 0;
}

