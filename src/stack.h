#ifndef LSP_STACK_H
#define LSP_STACK_H

#include <expr.h>

#include <string.h>

typedef struct stack_item_struct {
	expr_type * val;
	struct stack_item_struct * prev;
} stack_item_type;

void stack_item_init( stack_item_type * item, expr_type * val, stack_item_type * prev );
void stack_item_denit( stack_item_type * item );

typedef struct {
	stack_item_type * top;
	size_t size;
} stack_type;

void stack_init( stack_type * stack );

int stack_push( stack_type * stack, expr_type * expr );
void stack_pop( stack_type * stack );

expr_type * stack_top( stack_type * stack );
size_t stack_size( stack_type * stack );
expr_type * stack_at( stack_type * stack, size_t n );

#endif
