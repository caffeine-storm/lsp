#ifndef LSP_SCANNER_H
#define LSP_SCANNER_H

#include <stdlib.h>

struct int_callback_closure;
struct symbol_callback_closure;
struct string_callback_closure;

typedef struct {
  void (*on_int)( int n, struct int_callback_closure * c );
  struct int_callback_closure* int_callback_closure_;
  void (*on_symbol)( char const * s, size_t n, struct symbol_callback_closure * c );
  struct symbol_callback_closure* symbol_callback_closure_;
  void (*on_string)( char const * s, size_t n, struct string_callback_closure * c );
  struct string_callback_closure* string_callback_closure_;
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
