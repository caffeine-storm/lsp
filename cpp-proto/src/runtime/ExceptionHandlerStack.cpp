#include <runtime/ExceptionHandlerStack.hpp>

/******************************************************************************/

#include <runtime/UnhandledException.hpp>

/******************************************************************************/

namespace lsp {
namespace runtime {

/******************************************************************************/

void ExceptionHandlerStack::handle(lang::LspException & e) {
	// If there are no handlers, let the interpreter know.
	if(handlers_.empty()) {
		throw lsp::runtime::UnhandledException(e);
	}
}

/******************************************************************************/

}
}

/******************************************************************************/

