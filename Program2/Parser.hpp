#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"
#include "Text.hpp"
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
      void saveText(Text*);
      void saveElement(Element*);
    private:
      Element *root;
      String *tempString;
      std::stack<Element *> nodeStack;
      enum {
        start = 0,
        type_of_tag,
        name_or_namespace,
        must_be_name,
        close_name_or_namespace,
        close_must_be_name,
        inside_body,
        inside_text,
        tag_name_clear_ws
      } state;
  };

}
#endif
