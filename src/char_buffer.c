#include <char_buffer.h>

#include <lsp_assert.h>
#include <lsp_print.h>

#include <stdlib.h>
#include <string.h>

struct char_buffer_type_struct {
	struct {
		char * bytes;
		size_t num;
	} data;

	// Point into 'data.bytes'
	char * begin;
	char * end;

	FILE * from;
};

size_t spare_suffix( char_buffer_type const * buf ) {
	return buf->data.num - (buf->end - buf->data.bytes);
}

size_t spare_prefix( char_buffer_type const * buf ) {
	return buf->begin - buf->data.bytes;
}

void shift_prefix( char_buffer_type * buf ) {
	size_t shift_sz = spare_prefix( buf );
	memmove( buf->data.bytes, buf->begin, buf->data.num - shift_sz );
	buf->begin -= shift_sz;
	buf->end -= shift_sz;
}

char_buffer_type * make_char_buffer( FILE * from ) {
	char_buffer_type * ret = malloc( sizeof( char_buffer_type ) );
	char_buffer_init( ret, from );
	return ret;
}

void kill_char_buffer( char_buffer_type * buf ) {
	char_buffer_denit( buf );
	free( buf );
}

void char_buffer_init( char_buffer_type * buf, FILE * from ) {
	memset( buf, 0, sizeof( char_buffer_type ) );
	buf->from = from;
	buf->begin = buf->end = buf->data.bytes;
}

void char_buffer_denit( char_buffer_type * buf ) {
	free( buf->data.bytes );
}

size_t char_buffer_buffered( char_buffer_type const * buf ) {
	return buf->end - buf->begin;
}

int guarantee_extra_space( char_buffer_type * buf, size_t request ) {
	// Make sure there is at least 'request' bytes to spare at the end of 'buf'

	// Is it already there?
	if( spare_suffix( buf ) >= request ) {
		return 0;
	}

	// Would shifting be sufficient?
	if( spare_prefix( buf ) + spare_suffix( buf ) >= request ) {
		shift_prefix( buf );
		return 0;
	}

	// Need to expand our buffer.
	size_t old_sz = char_buffer_buffered( buf );
	size_t new_buf_sz = buf->data.num * 2;
	if( new_buf_sz < old_sz + request ) {
		new_buf_sz = old_sz + request;
	}
	char * new_buf = malloc( new_buf_sz );
	DEBUG( "char_buffer: allocated %ld bytes", new_buf_sz );
	if( !new_buf ) {
		return 1;
	}
	memmove( new_buf, buf->data.bytes, buf->data.num );
	free( buf->data.bytes );
	buf->data.bytes = new_buf;
	buf->data.num = new_buf_sz;
	buf->begin = buf->data.bytes;
	buf->end = buf->begin + old_sz;

	return 0;
}

size_t char_buffer_more( char_buffer_type * buf, void (*prompt_fn)() ) {
	// Extend 'data' with more bytes from the input stream.
	DEBUG( "eof?" );
	if( char_buffer_eof( buf ) ) {
		DEBUG( "eof? -> yep" );
		return 0;
	}
	DEBUG( "eof? -> nope" );

	int ret = guarantee_extra_space( buf, 512 );
	if( ret ) {
		LSP_ABORT( "failed to allocate memory for a char_buffer" );
	}

	DEBUG( "going to fgets..." );
	prompt_fn();
	char * s = fgets( buf->end, 512, buf->from );
	if( !s ) {
		if( feof( buf->from ) ) {
			return 0;
		}
		LSP_ABORT( "fgets failed" );
	}
	size_t num_read = strlen( buf->end );
	DEBUG( "read %ld bytes", num_read );
	buf->end += num_read;

	return num_read;
}

void char_buffer_seek( char_buffer_type * buf, size_t n ) {
	buf->begin += n;
	if( buf->begin >= buf->end ) {
		buf->begin = buf->data.bytes;
		buf->end = buf->begin;
	}
}

int char_buffer_eof( char_buffer_type const * buf ) {
	if( char_buffer_buffered( buf ) ) {
		return 0;
	}

	return feof( buf->from );
}

char const * char_buffer_begin( char_buffer_type const * buf ) {
	return buf->begin;
}

char const * char_buffer_end( char_buffer_type const * buf ) {
	return buf->end;
}

