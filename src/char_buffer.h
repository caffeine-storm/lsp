#ifndef LSP_CHAR_BUFFER_H
#define LSP_CHAR_BUFFER_H

#include <stdio.h>

struct char_buffer_type_struct;
typedef struct char_buffer_type_struct char_buffer_type;

char_buffer_type * char_buffer_alloc();
void char_buffer_free( char_buffer_type * buf );

void char_buffer_init( char_buffer_type * buf, FILE * from );
void char_buffer_denit( char_buffer_type * buf );

char_buffer_type * make_char_buffer( FILE * from );
void kill_char_buffer( char_buffer_type * buf );

size_t char_buffer_buffered( char_buffer_type const * buf );
size_t char_buffer_more( char_buffer_type * buf );
void char_buffer_seek( char_buffer_type * buf, size_t n );
int char_buffer_eof( char_buffer_type const * buf );

char const * char_buffer_begin( char_buffer_type const * buf );
char const * char_buffer_end( char_buffer_type const * buf );

#endif
