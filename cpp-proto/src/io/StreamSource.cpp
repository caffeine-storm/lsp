#include <io/StreamSource.hpp>

/******************************************************************************/

#include <iostream>
#include <string>

/******************************************************************************/

namespace lsp {
namespace io {

/******************************************************************************/


StreamSource::StreamSource( std::istream & in )
	: src_( in )
{
}

/******************************************************************************/

char StreamSource::next_() {
	char c = src_.get();
	if(!src_) {
		std::cout << "next_ hit something!" << std::endl;
	}
	if(c == std::char_traits<char>::eof()) {
		std::cout << "next_ hit eof!" << std::endl;
	}
	return c;
}

/******************************************************************************/

char StreamSource::peek_() const {
	char c = src_.peek();
	if(!src_) {
		std::cout << "peek_ hit something!" << std::endl;
	}
	if( c == std::char_traits<char>::eof()) {
		std::cout << "peek_ hit eof!" << std::endl;
	}
	return c;
}

/******************************************************************************/

bool StreamSource::has_more_() const {
	return !src_.eof();
}

/******************************************************************************/

}
}

/******************************************************************************/

