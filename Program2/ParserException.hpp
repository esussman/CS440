#ifndef EVAN_SUSSMAN_EXCEPTION
#define EVAN_SUSSMAN_EXCEPTION


#include <exception>

namespace xml
{
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
  };
}

#endif
