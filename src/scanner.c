#include <scanner.h>

#include <lsp_assert.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int all( char const * begin, char const * end, int (*fn)(int) ) {
	for( ; begin != end; ++begin ) {
		if( !(*fn)( *begin ) ) {
			return 0;
		}
	}
	return 1;
}

struct scanner_struct_type {
};

scanner_type * make_scanner() {
	scanner_type * ret = malloc( sizeof( scanner_type ) );
	scanner_init( ret );
	return ret;
}

void kill_scanner( scanner_type * scanner ) {
	scanner_denit( scanner );
	free( scanner );
}

void scanner_init( scanner_type * scanner ) {
	(void) scanner;
}

void scanner_denit( scanner_type * scanner ) {
	(void) scanner;
}

int parse_int( char const * begin, char const * end, int * out ) {
	char * buf;
	size_t n = end - begin;
	buf = malloc( n + 1 );
	strncpy( buf, begin, n );

	int ret = sscanf( buf, "%d", out );
	int e = errno;
	free( buf );

	if( e ) {
		return 1;
	}
	if( ret != 1 ) {
		return 1;
	}

	printf( "debug: parse_int parsed an int (%d)\n", *out );
	return 0;
}

int scanner_scan( scanner_type * scanner, char const * begin, char const * end, size_t * num_read_out, scanner_callback_type * callbacks ) {
	(void) scanner;

	if( begin == end ) {
		return scanner_scan_more;
	}

	int is_whitespace( char c ) {
		switch( c ) {
			case ' ':
			case '\t':
			case '\n':
				return 1;
			default:
				return 0;
		}
	}

	size_t num_read = 0;

	// Eat leading whitespace
	while( begin != end && is_whitespace( *begin ) ) {
		++num_read;
		++begin;
	}
	if( num_read ) {
		*num_read_out = num_read;
		return scanner_scan_ignore;
	}

	// We're either looking at a string, a symbol or a number.
	if( *begin == '"' ) {
		// It's a string!
		LSP_ABORT( "niy" );
	}

	// Find the next piece of whitespace
	char const * itr = begin;
	while( itr != end && !is_whitespace( *itr ) ) {
		++num_read;
		++itr;
	}
	if( itr == end ) {
		// Need more input
		return scanner_scan_more;
	}

	// '+' and '-' are symbols
	if( begin + 1 == itr && (*begin == '+' || *begin == '-') ) {
		LSP_ABORT( "niy" );
	}

	// [begin, itr) is either a number or a symbol.
	if( all( begin + 1, itr, isdigit ) ) {
		// The front has to be either a digit, a plus sign or a minus sign.
		if( *begin == '-' || *begin == '+' || isdigit( *begin ) ) {
			// number! Get its int value.
			int parsed;
			int ret = parse_int( begin, itr, &parsed );
			if( ret ) {
				return scanner_scan_reject;
			}
			callbacks->on_int( parsed );
			*num_read_out = itr - begin;
			return scanner_scan_token;
		}
	}

	// Everything else is a symbol!
	callbacks->on_symbol( begin, itr - begin );
	return scanner_scan_token;
}

