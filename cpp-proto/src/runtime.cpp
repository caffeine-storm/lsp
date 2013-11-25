#include <runtime.hpp>

/******************************************************************************/

#include <lang/UnboundName.hpp>
#include <lang/Value.hpp>
#include <parser/Token.hpp>
#include <runtime/ExceptionHandlerStack.hpp>
#include <runtime/UnhandledException.hpp>
#include <util/Unimplemented.hpp>

/******************************************************************************/

#include <algorithm>
#include <map>
#include <stdexcept>

/******************************************************************************/

namespace {

/******************************************************************************/

class NameNotFound : public std::runtime_error {
public:
	explicit
	NameNotFound(std::string const & s)
		: std::runtime_error(s)
	{
	}

	explicit
	NameNotFound(std::string && s)
		: std::runtime_error(std::move(s))
	{
	}

	char const * msg() const {
		return what();
	}
};

/******************************************************************************/

}

/******************************************************************************/

namespace lsp {
namespace runtime {

/******************************************************************************/

lang::Value eval(std::vector<std::shared_ptr<parser::Token>> const & v, ExceptionHandlerStack & handlers) {
	if(v.empty()) {
		throw std::runtime_error("Can't eval a null expression!");
	}

	std::vector<lang::Value> resolved(v.size());
	std::map<std::string, lang::Value> env; // TODO: pass as mutable reference
	// NIL is n in lsp
	env["n"] = lang::Value::NIL;

	auto resolve = [&env](std::shared_ptr<parser::Token> const & t) {
		auto itr = env.find(t->val());
		if(itr != env.end()) {
			return itr->second;
		}
		throw lang::UnboundName(t->val());
	};

	auto sink = resolved.begin();
	for(auto itr = v.begin(), end = v.end(); itr != end; ++itr ) {
		try {
			*sink++ = resolve(*itr);
		} catch(lang::UnboundName & e) {
			// TODO: maintain an exception handler stack and use it to handle
			// 'e'. Till then, report an error.
			handlers.handle(e);
		}
	}

	throw util::Unimplemented();
}

/******************************************************************************/

}
}

/******************************************************************************/
