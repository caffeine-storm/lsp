#include <parser.hpp>

/******************************************************************************/

#include <parser/Token.hpp>

/******************************************************************************/

namespace lsp {
namespace parser {

/******************************************************************************/

std::shared_ptr<Token> read_token(io::CharSource & in) {
	std::string tmp;

	char c = in.peek();

	if(c == '\n') {
		in.next();
		return std::make_shared<Token>("\n");
	}

	do {
		if(c == ' ') {
			in.next(); // Skip the space for next time.
			return std::make_shared<Token>(std::move(tmp));
		}

		if(c == '\n') { // Leave the \n in the stream for next time.
			return std::make_shared<Token>(std::move(tmp));
		}

		tmp.push_back(in.next());
		c = in.peek();
	} while(in.has_more());

	return std::make_shared<Token>(std::move(tmp));
}

/******************************************************************************/

}
}

/******************************************************************************/

