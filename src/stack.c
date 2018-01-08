#include <stack.h>

#include <lsp_assert.h>

#include <stdlib.h>

void stack_item_init( stack_item_type * item, expr_type * val, stack_item_type * prev ) {
	item->val = val;
	item->prev = prev;
}

void stack_item_denit( stack_item_type * item ) {
	expr_denit( item->val );
	item->prev = NULL;
}

void stack_init( stack_type * stack ) {
	stack->top = NULL;
	stack->size = 0;
}

int stack_push( stack_type * stack, expr_type * expr ) {
	stack_item_type * old_top = stack->top;
	// TODO: don't malloc each item; malloc arenas and allocate from the arena
	stack_item_type * new_top = malloc( sizeof( stack_item_type ) );

	if( !new_top ) {
		return 1;
	}

	stack_item_init( new_top, expr, old_top );
	stack->top = new_top;
	++stack->size;
	return 0;
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

expr_type * stack_top( stack_type * stack ) {
	return stack->top->val;
}
