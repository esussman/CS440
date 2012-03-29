#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"

namespace xml{

  class Parser {
    public:
      Parser();
      const Element* parse(const char *doc, size_t sz);
    private:
      Element *root;
      enum {
        start = 0,
        name_or_namespace
      } state;
  };

}
#endif
