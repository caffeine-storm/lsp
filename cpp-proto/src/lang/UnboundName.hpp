#ifndef LSP_LANG_UNBOUNDNAME_HPP
#define LSP_LANG_UNBOUNDNAME_HPP

/******************************************************************************/

#include <lang/LspException.hpp>

/******************************************************************************/

#include <string>

/******************************************************************************/

namespace lsp {
namespace lang {

/******************************************************************************/

class UnboundName : public LspException {
public:
	explicit
	UnboundName(std::string const & name)
		: LspException(name)
	{
	}

	explicit
	UnboundName(std::string && name)
		: LspException(std::move(name))
	{
	}

	virtual ~UnboundName() throw() {}

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_LANG_UNBOUNDNAME_HPP */

