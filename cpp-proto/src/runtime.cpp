#include <runtime.hpp>

/******************************************************************************/

#include <lang/Value.hpp>
#include <lang/UnboundName.hpp>
#include <parser/Token.hpp>
#include <util/Unimplemented.hpp>

/******************************************************************************/

#include <algorithm>
#include <map>
#include <stdexcept>

/******************************************************************************/

namespace lsp {
namespace runtime {

/******************************************************************************/

lang::Value eval(std::vector<std::shared_ptr<parser::Token>> const & v) {
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
	std::transform(v.begin(), v.end(), resolved.begin(), resolve);

	throw util::Unimplemented();
}

/******************************************************************************/

}
}

/******************************************************************************/
