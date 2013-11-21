/******************************************************************************/

#include <io/StreamSource.hpp>
#include <lang/Value.hpp>
#include <parser.hpp>
#include <parser/Token.hpp>
#include <runtime.hpp>
#include <util/Bail.hpp>

/******************************************************************************/

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

/******************************************************************************/

using namespace lsp;

/******************************************************************************/

namespace lsp {
namespace io {
void print(lang::Value const & v) {
	std::cerr << "[io::print]: unimplemented!" << std::endl;
}
}
}

/******************************************************************************/

namespace {

/******************************************************************************/

void print_prompt() {
	std::cout << "lsp> " << std::flush;
}

/******************************************************************************/

std::string show_expr(std::vector<std::shared_ptr<parser::Token>> const & v) {
	std::stringstream s;
	for(auto const & x : v) {
		s << x->val();
		s << " ";
	}
	return s.str();
}

/******************************************************************************/

}

/******************************************************************************/

int main(int argc, char * * argv) {
	std::shared_ptr<io::CharSource> cs(new io::StreamSource(std::cin));
	std::vector<std::shared_ptr<parser::Token>> cur_expr;

	while( true ) {
		if(cur_expr.empty()) {
			// Only print the prompt when we expect a new expression
			print_prompt();
		}

		if(!cs->has_more()) {
			std::cerr << "bye!" << std::endl;
			break;
		}

		std::shared_ptr<parser::Token> t = parser::read_token(*cs);
		if(!t) {
			util::bail("Couldn't read a token from char stream!");
		} else {
			std::cerr << "Got a token: '" << t->val() << "'" << std::endl;
		}
		if(t->val() == "\n") {
			if(cur_expr.empty()) {
				// Special Case: empty line
				continue;
			}
			std::cerr << "Got an expr: " << show_expr(cur_expr) << std::endl;
			lang::Value v = runtime::eval(cur_expr);
			io::print(v);
			cur_expr.clear();
		} else {
			cur_expr.emplace_back(std::move(t));
		}
	}

	return 0;
}

/******************************************************************************/

