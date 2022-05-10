#ifndef LSP_NAMESPACE_H
#define LSP_NAMESPACE_H

#include <expr.h>
#include <stack.h>

#include <stdlib.h>

typedef void (*callable_type)( stack_type * s, void* extra );

struct hash_struct;

typedef struct {
  struct hash_struct * table;
} namespace_type;

int namespace_init( namespace_type * ns );

int namespace_bind( namespace_type * ns, char const * name, callable_type fn );
int namespace_unbind( namespace_type * ns, char const * name );

callable_type namespace_get_symbol( namespace_type * ns, char const * name );

#endif
