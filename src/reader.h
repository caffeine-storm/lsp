#ifndef LSP_READER_H
#define LSP_READER_H

#include <char_buffer.h>
#include <expr.h>
#include <scanner.h>

#include <stdio.h>

enum read_result {
  read_result_ok,
  read_result_fail,
  read_result_fatal
};

typedef struct {
  char_buffer_type * buf;
  scanner_type * scanner;
  scanner_callback_type callbacks;
} reader_type;

int reader_init( reader_type * rdr, FILE * from );
void reader_denit( reader_type * rdr );

int reader_read_next( reader_type * rdr, expr_type * result, void (*prompt_fn)() );

#endif
