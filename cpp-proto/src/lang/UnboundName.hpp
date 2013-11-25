#ifndef LSP_LANG_UNBOUNDNAME_HPP
#define LSP_LANG_UNBOUNDNAME_HPP

/******************************************************************************/

#include <lang/LspException.hpp>

/******************************************************************************/

#include <sstream>
#include <string>

/******************************************************************************/

namespace lsp {
namespace lang {

/******************************************************************************/

class UnboundName : public LspException {
private:
	std::string make_message(std::string const & name) {
		std::stringstream msg;
		msg << "Couldn't find name '" << name << "'";
		return msg.str();
	}

public:
	explicit
	UnboundName(std::string const & name)
		: LspException(make_message(name))
	{
	}

	virtual ~UnboundName() throw() {}

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_LANG_UNBOUNDNAME_HPP */

