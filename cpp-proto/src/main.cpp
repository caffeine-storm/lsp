/******************************************************************************/

#include <io/StreamSource.hpp>

/******************************************************************************/

#include <iostream>
#include <memory>

/******************************************************************************/

int main(int argc, char * * argv) {
	std::shared_ptr<lsp::io::CharSource> cs(new lsp::io::StreamSource(std::cin));
	while( true ) {
		break;
		// Token t = read_token( *cs );
	}
	return 0;
}

/******************************************************************************/

