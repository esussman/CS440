#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"
#include <stack>
namespace xml{

  class Parser {
    public:
      Parser();
      const Element* parse(const char *doc, size_t sz);
      bool isProperName(String);
      void resetTempString(const char*);
      bool isValidNameChar(const char);
      bool isValidTextChar(const char);
    private:
      Element *root;
      String *tempString;
      std::stack<Element *> nodeStack;
      enum {
        start = 0,
        name_or_namespace,
        close_name_or_namespace,
        inside_body
      } state;
  };

}
#endif
