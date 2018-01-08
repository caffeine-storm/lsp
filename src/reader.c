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
	(void) from;
	(void) result;
	return 1;
}

