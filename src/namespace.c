#include <namespace.h>

#include <lsp_assert.h>

#include <string.h>

// Sourced from www.cse.yorku.ca/~oz/hash.html
size_t djb2( char const * s ) {
  size_t ret = 5381;
  int c;
  while( *s ) {
    c = *s++;
    ret = ((ret << 5) + ret) + c;
  }
  return ret;
}

// Linked list storing a callable and the symbol bound to that callable.
struct entry_list {
  callable_type entry;
  char * name;
  struct entry_list * next;
};

int entry_list_append( struct entry_list * head, callable_type fn, char * name ) {
  // Handle appending to the empty list
  if( !head->name ) {
    head->entry = fn;
    head->name = name;
    return 0;
  }

  while( head->next ) {
    head = head->next;
  }

  head->next = malloc( sizeof( struct entry_list ) );
  if( !head->next ) {
    return 1;
  }
  head = head->next;

  head->entry = fn;
  head->name = name;
  head->next = NULL;

  return 0;
}

struct entry_list * entry_list_search( struct entry_list * head, char const * name ) {
  if( !head->name ) {
    // Empty entry_list
    return NULL;
  }

  while( head ) {
    // Does 'name' match the current entry?
    if( !strcmp( name, head->name ) ) {
      return head;
    }

    head = head->next;
  }

  return NULL;
}

int entry_list_remove( struct entry_list * head, char const * name ) {
  // Was the list empty to begin with?
  if( !head->name ) {
    return 1;
  }

  // Does the first node match 'name'? It's a special case because we
  // wouldn't want to call 'free( head )'.
  if( !strcmp( head->name, name ) ) {
    free( head->name );
    if( head->next ) {
      head->name = head->next->name;
      head->entry = head->next->entry;
      head->next = head->next->next;
    } else {
      head->name = NULL;
      head->entry = NULL;
    }
    return 0;
  }

  struct entry_list * prev = head;
  head = head->next;
  while( head ) {
    // Does the current node hold the entry for 'name'?
    if( !strcmp( head->name, name ) ) {
      // Clean up memory owned by the head
      free( head->name );

      // Was the head the end of list?
      if( !head->next ) {
        // Overwrite the previous node to be end-of-list
        prev->next = NULL;
        free( head );
      } else {
        // Overwrite the head with the next node in the list
        head->name = head->next->name;
        head->entry = head->next->entry;
        struct entry_list * dangling = head->next;
        head->next = head->next->next;
        free( dangling );
      }
      return 0;
    }

    prev = head;
    head = head->next;
  }

  // Didn't find a node matching 'name'
  return 1;
}

struct hash_struct {
  struct {
    struct entry_list * data;
    size_t len;
  } buckets;
  size_t num_entries;
};

int hash_init_sz( struct hash_struct * table, size_t n ) {
  table->buckets.data = calloc( n, sizeof(struct entry_list) );
  if( !table->buckets.data ) {
    return 1;
  }
  table->buckets.len = n;
  table->num_entries = 0;
  return 0;
}

int hash_init( struct hash_struct * table ) {
  return hash_init_sz( table, 8 );
}

void hash_denit( struct hash_struct * table ) {
  free( table->buckets.data );
}

float hash_load_factor( struct hash_struct * table ) {
  return table->num_entries / table->buckets.len;
}

int hash_add( struct hash_struct * table, char * name, callable_type fn );
int hash_extend( struct hash_struct * table ) {
  size_t newlen = table->buckets.len * 2;
  struct hash_struct temp_table;
  hash_init_sz( &temp_table, newlen );

  // Walk the given table adding the entries to the temp table.
  struct entry_list * * bucket_itr = &table->buckets.data;
  struct entry_list * * bucket_end = bucket_itr + table->buckets.len;
  for( ; bucket_itr != bucket_end; ++bucket_itr ) {
    struct entry_list * head = *bucket_itr;
    if( !head->name ) {
      continue;
    }

    while( head ) {
      hash_add( &temp_table, head->name, head->entry );
      head = head->next;
    }
  }
  LSP_ASSERT( table->num_entries == temp_table.num_entries, "All of the entries should have been copied!" );

  free( table->buckets.data );
  table->buckets = temp_table.buckets;

  return 0;
}

struct entry_list * hash_entry( struct hash_struct * table, char const * name ) {
  size_t n = djb2( name );
  n %= table->buckets.len;
  return table->buckets.data + n;
}

int hash_add( struct hash_struct * table, char * name, callable_type fn ) {
  struct entry_list * head = hash_entry( table, name );
  int ret = entry_list_append( head, fn, name );

  if( ret ) {
    free( name );
    return ret;
  }

  ++table->num_entries;
  if( hash_load_factor( table ) > 0.8 ) {
    ret = hash_extend( table );
  }

  return ret;
}

int hash_remove( struct hash_struct * table, char const * name ) {
  struct entry_list * head = hash_entry( table, name );
  return entry_list_remove( head, name );
}

callable_type hash_lookup( struct hash_struct * table, char const * name ) {
  struct entry_list * head = hash_entry( table, name );
  head = entry_list_search( head, name );

  if( !head ) {
    return NULL;
  }

  return head->entry;
}

int namespace_init( namespace_type * ns ) {
  ns->table = malloc( sizeof( struct hash_struct ) );
  if( !ns->table ) {
    return 1;
  }

  int ret = hash_init( ns->table );
  if( ret ) {
    free( ns->table );
    return ret;
  }

  return 0;
}

int namespace_bind( namespace_type * ns, char const * name, callable_type fn) {
  size_t sz = strlen( name ) + 1;
  char * name_copy = malloc( sz );
  if( !name_copy ) {
    return 1;
  }

  strncpy( name_copy, name, sz );
  return hash_add( ns->table, name_copy, fn );
}

int namespace_unbind( namespace_type * ns, char const * name ) {
  return hash_remove( ns->table, name );
}

callable_type namespace_get_symbol( namespace_type * ns, char const * name ) {
  return hash_lookup( ns->table, name );
}

