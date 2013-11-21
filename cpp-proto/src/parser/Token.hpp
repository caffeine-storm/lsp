#ifndef LSP_PARSER_TOKEN_HPP
#define LSP_PARSER_TOKEN_HPP

/******************************************************************************/

#include <string>

/******************************************************************************/

namespace lsp {
namespace parser {

/******************************************************************************/

class Token {
public:
	explicit
	Token(std::string const & val):
		val_(val)
	{
	}

	explicit
	Token(std::string && val):
		val_(val)
	{
	}

	Token(Token const & other) = default;
	Token(Token && other) = default;

	Token & operator=(Token const & other) = default;
	Token & operator=(Token && other) = default;

public:
	std::string const & val() const {
		return val_;
	}

private:
	std::string val_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_PARSER_TOKEN_HPP */

