#include <lsp_util.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

char * lsp_strdup( char const * s ) {
	size_t len = strlen( s );
	char * ret = malloc( len + 1 );
	if( !ret ) {
		return NULL;
	}
	strcpy( ret, s );
	return ret;
}

char * lsp_strndup( char const * s, size_t n ) {
	char * ret = malloc( n + 1 );
	if( !ret ) {
		errno = ENOMEM;
		return NULL;
	}

	char * itr = ret;
	while( n-- && *s ) {
		*itr++ = *s++;
	}
	*itr = 0;

	return ret;
}

