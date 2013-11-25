#ifndef LSP_RUNTIME_EXCEPTIONHANDLERSTACK_HPP
#define LSP_RUNTIME_EXCEPTIONHANDLERSTACK_HPP

/******************************************************************************/

#include <stack>

/******************************************************************************/

namespace lsp {

/******************************************************************************/

namespace lang {
class LspException;
}

/******************************************************************************/

namespace runtime {

/******************************************************************************/

class ExceptionHandlerStack {
public:
	void handle(lang::LspException & e);

private:
	std::stack<void *> handlers_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_RUNTIME_EXCEPTIONHANDLERSTACK_HPP */

