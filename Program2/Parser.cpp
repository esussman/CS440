#include "Parser.hpp"
#include "String.hpp"

xml::Parser::Parser()
{
  state = start;
  root = NULL;
}

const xml::Element* xml::Parser::parse(const char*doc, size_t sz)
{
  state = start;
  xml::String hold;
  for(unsigned int i = 0; i < sz; i++)
  {
    const char data = doc[i];
    while(true)
    {
      switch(state)
      {
        case start:
          if(isspace(data))
          {
            //just go to next character...
          }
          else if(data == '<')
          {
            state = name_or_namespace;
          }
          else
          {
            //throw error bad input
          }
              break;
        case name_or_namespace:
          if(isspace(data))
          {

          }
              break;
      }
      break;
    }
  }
  return 0;
}
