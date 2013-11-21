#include <parser.hpp>

/******************************************************************************/

#include <parser/Token.hpp>

/******************************************************************************/

namespace lsp {
namespace parser {

/******************************************************************************/

std::shared_ptr<Token> read_token(io::CharSource & in) {
	std::string tmp;

	if(in.peek() == '\n') {
		in.next();
		return std::make_shared<Token>("\n");
	}

	while(in.has_more()) {
		char c = in.peek();
		if(c == ' ') {
			in.next(); // Skip the space for next time.
			return std::make_shared<Token>(std::move(tmp));
		}

		if(c == '\n') {
			return std::make_shared<Token>(std::move(tmp));
		}

		tmp.push_back(in.next());
	}

	return std::make_shared<Token>(std::move(tmp));
}

/******************************************************************************/

}
}

/******************************************************************************/

