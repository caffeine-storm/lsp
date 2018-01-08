#ifndef LSP_EXPR_H
#define LSP_EXPR_H

enum EXPR_TYPE {
	EXPR_TYPE_NIL,
	EXPR_TYPE_SYMBOL,
	EXPR_TYPE_INT,
	EXPR_TYPE_EOF
};

typedef struct {
	int type_code; // One of EXPR_TYPE
	union {
		int int_val;
		char * symbol;
	} val; // Which member of the union to use is encoded by 'type_code'
} expr_type;

void expr_init( expr_type * expr );
void expr_denit( expr_type * expr );

int expr_get_int( expr_type * expr );
void expr_set_int( expr_type * expr, int val );

void expr_set_eof( expr_type * expr );

char * expr_get_symbol( expr_type * expr );

#endif
