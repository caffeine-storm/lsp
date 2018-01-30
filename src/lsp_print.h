#ifndef LSP_PRINT_H
#define LSP_PRINT_H

#include <stdio.h>

#if defined(LSP_TRACE)
#define TRACE( msg, ... ) \
	fprintf( stderr, "trace: " __FILE__ ":%d: " msg "\n", __LINE__, ##__VA_ARGS__ )
#else
#define TRACE( msg, ... )
#endif

#if defined(LSP_DEBUG) || defined(LSP_TRACE)
#define DEBUG( msg, ... ) \
	fprintf( stderr, "debug: " __FILE__ " " msg "\n", ##__VA_ARGS__ )
#else
#define DEBUG( msg, ... )
#endif

#endif

