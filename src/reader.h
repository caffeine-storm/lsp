#ifndef LSP_READER_H
#define LSP_READER_H

#include <expr.h>

#include <stdio.h>

enum read_result {
	read_result_ok,
	read_result_fail,
	read_result_fatal
};

typedef struct {
} reader_type;

void reader_init( reader_type * rdr );
void reader_denit( reader_type * rdr );

int reader_read( reader_type * rdr, FILE * from, expr_type * result );

#endif
