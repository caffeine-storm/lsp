#ifndef LSP_RUNTIME_UNHANDLEDEXCEPTION_HPP
#define LSP_RUNTIME_UNHANDLEDEXCEPTION_HPP

/******************************************************************************/

#include <lang/LspException.hpp>

/******************************************************************************/

#include <stdexcept>

/******************************************************************************/

namespace lsp {
namespace runtime {

/******************************************************************************/

class UnhandledException : public std::runtime_error {
public:
	explicit
	UnhandledException(lang::LspException const & e)
		: std::runtime_error("Unhandled Exception"),
		wrapped_(e)
	{
	}

	explicit
	UnhandledException(lang::LspException && e)
		: std::runtime_error("Unhandled Exception"),
		wrapped_(std::move(e))
	{
	}

	virtual
	~UnhandledException() throw() {}

	lang::LspException const & wrapped() const {
		return wrapped_;
	}

private:
	lang::LspException wrapped_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_RUNTIME_UNHANDLEDEXCEPTION_HPP */

