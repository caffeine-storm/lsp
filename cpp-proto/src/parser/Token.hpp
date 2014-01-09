#ifndef LSP_PARSER_TOKEN_HPP
#define LSP_PARSER_TOKEN_HPP

/******************************************************************************/

#include <string>

/******************************************************************************/

namespace lsp {
namespace parser {

/******************************************************************************/

enum class TokenType {
	NAME,
	INT_LIT,
	STR_LIT
};

/******************************************************************************/

class Token {
public:
	explicit
	Token(std::string const & val, TokenType tp)
		: val_(val),
		tp_(tp)
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

	TokenType type() const {
		return tp_;
	}

private:
	std::string val_;
	TokenType tp_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_PARSER_TOKEN_HPP */

