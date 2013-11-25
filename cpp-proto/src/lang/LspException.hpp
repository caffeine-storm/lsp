#ifndef LSP_LANG_LSPEXCEPTION_HPP
#define LSP_LANG_LSPEXCEPTION_HPP

/******************************************************************************/

#include <string>

/******************************************************************************/

namespace lsp {
namespace lang {

/******************************************************************************/

class LspException {
public:
	explicit
	LspException(std::string const & s)
		: msg_(s)
	{
	}

	explicit
	LspException(std::string && s)
		: msg_(std::move(s))
	{
	}

	std::string const & msg() const {
		return msg_;
	}

private:
	std::string msg_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_LANG_LSPEXCEPTION_HPP */

