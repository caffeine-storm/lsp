#ifndef LSP_SCANNER_H
#define LSP_SCANNER_H

#include <stdlib.h>

typedef struct {
	void (*on_int)( int n );
	void (*on_symbol)( char const * s, size_t n );
} scanner_callback_type;

struct scanner_struct_type;
typedef struct scanner_struct_type scanner_type;

scanner_type * make_scanner();
void kill_scanner( scanner_type * scanner );

void scanner_init( scanner_type * scanner );
void scanner_denit( scanner_type * scanner );

enum scanner_scan_result {
	scanner_scan_ignore,
	scanner_scan_more,
	scanner_scan_token,
	scanner_scan_reject
};

int scanner_scan( scanner_type * scanner, char const * begin, char const * end, size_t * num_read_out, scanner_callback_type * callbacks );

#endif
