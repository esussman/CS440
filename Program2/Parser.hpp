#ifndef EVAN_SUSSMAN_PARSER
#define EVAN_SUSSMAN_PARSER

#include "Element.hpp"
#include "Text.hpp"
#include <stack>
#include <exception>

namespace xml{

  class Parser {
    public:
      Parser();
      class ParserError : public std::exception {
        friend class Parser;
        public:
          ParserError(const char* m = "Parse Error") : msg(m) {};
          ~ParserError() throw() {};
          virtual const char *what() const throw()
          {
            return msg;
          }
        private:
          const char* msg;
      } ParserError;
      const Element* parse(const char *doc, size_t sz);
      bool isProperName(String);
      void resetTempString(const char*);
      bool isValidNameChar(const char);
      bool isValidTextChar(const char);
      void saveText(Text*);
    private:
      Element *root;
      String *tempString;
      std::stack<Element *> nodeStack;
      enum {
        start = 0,
        name_or_namespace,
        close_name_or_namespace,
        inside_body,
        inside_text
      } state;
  };

}
#endif
