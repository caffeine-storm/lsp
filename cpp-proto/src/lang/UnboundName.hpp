#ifndef LSP_LANG_UNBOUNDNAME_HPP
#define LSP_LANG_UNBOUNDNAME_HPP

/******************************************************************************/

#include <exception>
#include <string>

/******************************************************************************/

namespace lsp {
namespace lang {

/******************************************************************************/

class UnboundName : public std::exception {
public:
	explicit
	UnboundName(std::string const & name)
		: name_(name)
	{
	}

	explicit
	UnboundName(std::string && name)
		: name_(std::move(name))
	{
	}

	std::string const & name() const {
		return name_;
	}

	virtual ~UnboundName() throw() {}

private:
	std::string name_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_LANG_UNBOUNDNAME_HPP */
