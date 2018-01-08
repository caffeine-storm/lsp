#include <lsp_assert.h>

#include <stdio.h>
#include <stdlib.h>

void lsp_abort( char const * const filename, int lineno, char const * msg ) {
	printf( "LSP-ABORT: %s:%d: %s\n", filename, lineno, msg );
	exit( 2 );
}

