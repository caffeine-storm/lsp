#ifndef LSP_IO_STREAMSOURCE_HPP
#define LSP_IO_STREAMSOURCE_HPP

/******************************************************************************/

#include <istream>

/******************************************************************************/

namespace lsp {
namespace io {

/******************************************************************************/

class StreamSource : public CharSource {
public:
	explicit
	StreamSource( std::istream & in );

private:
	virtual char next_();
	virtual char peek_() const;
	virtual bool has_more_() const;

private:
	std::istream & src_;

};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_IO_STREAMSOURCE_HPP */

