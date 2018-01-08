#include <reader.h>

#include <string.h>

void reader_init( reader_type * rdr ) {
	memset( rdr, 0, sizeof( reader_type ) );
}

void reader_denit( reader_type * rdr ) {
	(void) rdr;
}

int reader_read( reader_type * rdr, FILE * from, expr_type * result ) {
	(void) rdr;

	char buf[512] = {0};
	int bytes_read = fread( buf, sizeof( buf ), 1, from );
	(void) bytes_read;

	// Have we read the entire input stream?
	if( feof( from ) ) {
		// Yield a EOF expr
		expr_set_eof( result );
		return read_result_ok;
	}

	return read_result_fatal;
}

