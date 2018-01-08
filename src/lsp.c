#include <expr.h>
#include <lsp_assert.h>
#include <printer.h>
#include <reader.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum EVAL_RESULT {
	EVAL_PUSH_EXPR,
	EVAL_EXIT,
	EVAL_ERROR
};

typedef struct stack_item_struct {
	expr_type * val;
	struct stack_item_struct * prev;
} stack_item_type;

void stack_item_init( stack_item_type * item, expr_type * val, stack_item_type * prev ) {
	item->val = val;
	item->prev = prev;
}

void stack_item_denit( stack_item_type * item ) {
	expr_denit( item->val );
	item->prev = NULL;
}

typedef struct {
	stack_item_type * top;
	size_t size;
} stack_type;

int stack_push( stack_type * stack, expr_type * expr );
void stack_init( stack_type * stack ) {
	expr_type * canary = malloc( sizeof( expr_type ) );
	expr_init( canary );
	expr_set_int( canary, 0 );
	stack->size = 0;
	stack_push( stack, canary );
}

// TODO: warn about ignored return value
int stack_push( stack_type * stack, expr_type * expr ) {
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

expr_type * stack_top( stack_type * stack ) {
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
		if( !ret ) {
			printf( "read-failure: <TODO: descriptive error message>\n" );
			continue;
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
    printf( "Hello World!\n" );
    return 0;
}

