#include <expr.h>
#include <lsp_assert.h>

#include <stdlib.h>
#include <string.h>

expr_type * make_expr() {
  expr_type * ret = malloc( sizeof( expr_type ) );
  expr_init( ret );
  return ret;
}

void kill_expr( expr_type * e ) {
  expr_denit( e );
  free( e );
}

void expr_init( expr_type * expr ) {
  expr->type_code = EXPR_TYPE_NIL;
  memset( &expr->val, 0, sizeof( expr->val ) );
}

void expr_denit( expr_type * expr ) {
  switch( expr->type_code ) {
    case EXPR_TYPE_SYMBOL: {
      free( expr->val.symbol );
      return;
    }
    case EXPR_TYPE_NIL:
    case EXPR_TYPE_INT:
      ;
  }
}

int expr_get_int( expr_type * expr ) {
  LSP_ASSERT( expr->type_code == EXPR_TYPE_INT, "Can only get int value from a int expression!" );
  return expr->val.int_val;
}

void expr_set_int( expr_type * expr, int val ) {
  expr_denit( expr );
  expr->type_code = EXPR_TYPE_INT;
  expr->val.int_val = val;
}

void expr_set_eof( expr_type * expr ) {
  LSP_ASSERT( expr->type_code == EXPR_TYPE_NIL, "Can't overwrite an expression to be EOF" );
  expr->type_code = EXPR_TYPE_EOF;
}

char * expr_get_symbol( expr_type * expr ) {
  LSP_ASSERT( expr->type_code == EXPR_TYPE_SYMBOL, "Can only get a symbol value from a symbol expression!" );
  return expr->val.symbol;
}

void expr_set_symbol( expr_type * expr, char * sym ) {
  expr->type_code = EXPR_TYPE_SYMBOL;
  expr->val.symbol = sym;
}

char * expr_get_string( expr_type * expr ) {
  LSP_ASSERT( expr->type_code == EXPR_TYPE_STRING, "Can only get a string value from a string expression!" );
  return expr->val.symbol;
}

void expr_set_string( expr_type * expr, char * str ) {
  expr->type_code = EXPR_TYPE_STRING;
  expr->val.symbol = str;
}

