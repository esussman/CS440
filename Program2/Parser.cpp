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
    while(true)
    {
      switch(state)
      {
        case start:
              break;
        case name_or_namespace:
              break;
      }
    }
  }
  return 0;
}
