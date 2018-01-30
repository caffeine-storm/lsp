#ifndef LSP_UTIL_H
#define LSP_UTIL_H

#include <stdlib.h>

#ifndef strdup
#define strdup lsp_strdup
char * lsp_strdup( char const * s );
#endif

#ifndef strndup
#define strndup lsp_strndup
char * lsp_strndup( char const * s, size_t n );
#endif

#endif

