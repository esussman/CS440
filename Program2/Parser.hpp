#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"

namespace xml{

  class Parser {
    public:
      Parser();
      const Element* parse(const char *doc, size_t sz);
      bool isProperName(String);
    private:
      Element *root;
      String *tempString;
      enum {
        start = 0,
        name_or_namespace
      } state;
  };

}
#endif
