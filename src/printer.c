#include <printer.h>

#include <lsp_assert.h>

#include <assert.h>
#include <string.h>

void printer_print( printer_type * printer, expr_type * expr, FILE * out ) {
	(void) printer;
	switch( expr->type_code ) {
		case EXPR_TYPE_NIL: {
			fprintf( out, "n" );
			return;
		}
		case EXPR_TYPE_SYMBOL: {
			// For now, the only symbol is 'exit'
			assert( strcmp( expr_get_symbol( expr ), "exit" ) == 0 );
			fprintf( out, "exit" );
			return;
		}
		case EXPR_TYPE_INT: {
			fprintf( out, "%d", expr_get_int( expr ) );
			return;
		}
		case EXPR_TYPE_EOF: {
			fprintf( out, "<EOF>" );
			return;
		}
		default: {
			// fall-through
		}
	}
	LSP_ABORT( "Unknown expr type" );
}

