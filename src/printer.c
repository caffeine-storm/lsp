#include <printer.h>

#include <lsp_assert.h>

#include <assert.h>
#include <string.h>

void printer_print( printer_type * printer, expr_type * expr, FILE * out ) {
  (void) printer;
  switch( expr->type_code ) {
    case EXPR_TYPE_NIL: {
      fprintf( out, "n\n" );
      return;
    }
    case EXPR_TYPE_INT: {
      fprintf( out, "%d\n", expr_get_int( expr ) );
      return;
    }
    case EXPR_TYPE_STRING: {
      fprintf( out, "\"%s\"\n", expr_get_string( expr ) );
      return;
    }
    case EXPR_TYPE_SYMBOL: {
      fprintf( out, "%s\n", expr_get_symbol( expr ) );
      return;
    }
    case EXPR_TYPE_EOF: {
      fprintf( out, "<EOF>\n" );
      return;
    }
    default: {
      // fall-through
    }
  }
  LSP_ABORT( "Unknown expr type" );
}

