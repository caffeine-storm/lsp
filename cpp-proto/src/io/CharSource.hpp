#ifndef LSP_IO_CHARSOURCE_HPP
#define LSP_IO_CHARSOURCE_HPP

/******************************************************************************/

namespace lsp {
namespace io {

/******************************************************************************/

class CharSource {
public:
	char next() {
		return next_();
	}

	char peek() const {
		return peek_();
	}

	bool has_more() const {
		return has_more_();
	}

private:
	virtual char next_() = 0;
	virtual char peek_() const = 0;
	virtual bool has_more_() const = 0;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_IO_CHARSOURCE_HPP */

