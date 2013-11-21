#ifndef LSP_UTIL_UNIMPLEMENTED
#define LSP_UTIL_UNIMPLEMENTED

/******************************************************************************/

#include <exception>

/******************************************************************************/

namespace lsp {
namespace util {

/******************************************************************************/

class Unimplemented : public std::exception {
};

/******************************************************************************/

}
}

/******************************************************************************/

#endif /* LSP_UTIL_UNIMPLEMENTED */
