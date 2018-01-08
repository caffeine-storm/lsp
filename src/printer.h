#ifndef LSP_PRINTER_H
#define LSP_PRINTER_H

#include <expr.h>

#include <stdio.h>

typedef struct {
} printer_type;

void printer_print( printer_type * printer, expr_type * expr, FILE * out );

#endif
