#ifndef LSP_ASSERT_H
#define LSP_ASSERT_H

#include <assert.h>
#include <stdnoreturn.h>

#define LSP_ABORT( msg ) do { \
  lsp_abort( __FILE__, __LINE__, msg ); \
} while( 0 )

#define LSP_ASSERT( cond, msg ) do { \
  if( !( cond ) ) { \
    lsp_abort( __FILE__, __LINE__, msg ); \
  } \
} while( 0 )

noreturn void lsp_abort( char const * const filename, int lineno, char const * msg );

#endif
