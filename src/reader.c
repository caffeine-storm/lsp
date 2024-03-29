#include <reader.h>

#include <lsp_assert.h>
#include <lsp_print.h>
#include <lsp_util.h>

#include <errno.h>
#include <string.h>

struct int_callback_closure {
  expr_type * result;
};
void yield_int( int n, struct int_callback_closure * c ) {
  DEBUG( "reader: yielding int (%d)", n );
  expr_set_int( c->result, n );
}

struct symbol_callback_closure {
  expr_type * result;
};
void yield_symbol( char const * str, size_t n, struct symbol_callback_closure * c ) {
  char * mystr = strndup( str, n );
  if( !mystr ) {
    LSP_ABORT( "couldn't allocate memory to copy a symbol!" );
  }
  expr_set_symbol( c->result, mystr );
}

struct string_callback_closure {
  expr_type * result;
};
void yield_string( char const * str, size_t n, struct string_callback_closure * c ) {
  char * mystr = strndup( str, n );
  if( !mystr ) {
    LSP_ABORT( "couldn't allocate memory to copy a string!" );
  }
  expr_set_string( c->result, mystr );
}

int reader_init( reader_type * rdr, FILE * from ) {
  rdr->buf = make_char_buffer( from );
  if( !rdr->buf ) {
    return 1;
  }

  rdr->scanner = make_scanner( &rdr->callbacks );
  if( !rdr->scanner ) {
    kill_char_buffer( rdr->buf );
    return 1;
  }

  return 0;
}

void reader_denit( reader_type * rdr ) {
  kill_scanner( rdr->scanner );
  kill_char_buffer( rdr->buf );
  if (rdr->callbacks.int_callback_closure_) {
    free(rdr->callbacks.int_callback_closure_);
  }
  if (rdr->callbacks.string_callback_closure_) {
    free(rdr->callbacks.string_callback_closure_);
  }
  if (rdr->callbacks.symbol_callback_closure_) {
    free(rdr->callbacks.symbol_callback_closure_);
  }
}

int reader_read_next( reader_type * rdr, expr_type * result, void (*prompt_fn)() ) {
  int ret = 0;
  // If nothing is buffered yet, pull more characters from the input stream
  if( !char_buffer_buffered( rdr->buf ) ) {
    DEBUG( "nothing buffered" );
    ret = char_buffer_more( rdr->buf, prompt_fn );
    DEBUG( "buffer_more returned %d", ret );
    if( !ret ) {
      // Was that eof, or error?
      if( char_buffer_eof( rdr->buf ) ) {
        expr_set_eof( result );
        return read_result_ok;
      }

      LSP_ABORT( "Couldn't buffer more input!" );
    }
  }

  // Iterate the buffered bytes looking for an expression-literal
  char const * begin = char_buffer_begin( rdr->buf );
  char const * end = char_buffer_end( rdr->buf );

  rdr->callbacks.on_int = &yield_int;
  rdr->callbacks.int_callback_closure_ = malloc(sizeof(struct int_callback_closure));
  if (!rdr->callbacks.int_callback_closure_) {
    LSP_ABORT( "couldn't allocate memory for int_callback_closure" );
  }
  rdr->callbacks.int_callback_closure_->result = result;

  rdr->callbacks.on_symbol = &yield_symbol;
  rdr->callbacks.symbol_callback_closure_ = malloc(sizeof(struct symbol_callback_closure));
  if (!rdr->callbacks.symbol_callback_closure_) {
    LSP_ABORT( "couldn't allocate memory for symbol_callback_closure" );
  }
  rdr->callbacks.symbol_callback_closure_->result = result;

  rdr->callbacks.on_string = &yield_string;
  rdr->callbacks.string_callback_closure_ = malloc(sizeof(struct string_callback_closure));
  if (!rdr->callbacks.string_callback_closure_) {
    LSP_ABORT( "couldn't allocate memory for string_callback_closure" );
  }
  rdr->callbacks.string_callback_closure_->result = result;

  while( 1 ) {
    size_t num_read;
    DEBUG( "going to scan" );
    ret = scanner_scan( rdr->scanner, begin, end, &num_read, &rdr->callbacks );
    DEBUG( "scanner_scan returned %d", ret );
    switch( ret ) {
      case scanner_scan_ignore: {
        char_buffer_seek( rdr->buf, num_read );
        begin = char_buffer_begin( rdr->buf );
        end = char_buffer_end( rdr->buf );
        continue;
      }
      case scanner_scan_more: {
        // The scanner hit the end of the buffer but wasn't in a
        // rejecting state... need to buffer more data and continue
        // scanning.
        ret = char_buffer_more( rdr->buf, prompt_fn );
        if( !ret ) {
          // eof?
          if( char_buffer_eof( rdr->buf ) ) {
            expr_set_eof( result );
            return read_result_ok;
          }
        }
        begin = char_buffer_begin( rdr->buf );
        end = char_buffer_end( rdr->buf );
        break;
      }
      case scanner_scan_reject: {
        return read_result_fatal;
      }
      case scanner_scan_token: {
        // Before returning 'scanner_scan_token', the scanner will have
        // invoked the appropriated callback closure to assign a
        // meaningful value to 'result'.
        TRACE( "seeking char buffer by %zd", num_read );
        char_buffer_seek( rdr->buf, num_read );
        return read_result_ok;
      }
      default:
        LSP_ABORT( "snh" );
    }

    // Have we exhausted the input stream?
    if( num_read == 0 && char_buffer_eof( rdr->buf ) ) {
      // Yield an EOF expr
      expr_set_eof( result );
      return read_result_ok;
    }
  }
}

