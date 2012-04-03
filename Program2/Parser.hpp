#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"
#include "Text.hpp"
#include <stack>
#include <map>

namespace xml{

  class Parser {
    public:
      Parser();
      const Element* parse(const char *doc, size_t sz);
      bool isProperName(String);
      void resetTempString(const char*);
      bool isValidNameChar(const char);
      bool isValidTextChar(const char);
      bool isValidAddressChar(const char);
      void saveText(Text*);
      void saveElement(Element*);
    private:
      Element *root;
      String *tempString;
      std::stack<Element *> nodeStack;
      std::stack<std::map<const String, String>> nmspaceStack;
      enum {
        start = 0,
        type_of_tag,
        name_or_namespace,
        must_be_name,
        close_name_or_namespace,
        close_must_be_name,
        def_namespace_name,
        namespace_quote,
        namespace_definition,
        end_namespace_definition_ws,
        check_xmlns,
        inside_body,
        inside_text,
        tag_name_clear_ws,
        close_tag_name_clear_ws
      } state;
  };

}
#endif
