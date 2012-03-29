#include "Parser.hpp"
#include "String.hpp"

xml::Parser::Parser()
{
  state = start;
  tempString = NULL;
  root = NULL;
}
void xml::Parser::resetTempString(const char* string)
{
  if(tempString == NULL)
    tempString = new String(string,1);
}
bool xml::Parser::isValidChar(const char data)
{
  return isalnum(data) || data == '_';
}
const xml::Element* xml::Parser::parse(const char*doc, size_t sz)
{
  state = start;
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
          resetTempString(doc+i);
          if(isspace(data))
          {

          }
          else if(data == '/')
          {
            //close tag
          }
          else if(data == ':')
          {
            //new state
          }
          else if(isValidChar(data))
          {
            (*tempString).append(1);
          }

              break;
      }
      break;
    }
  }
  return 0;
}
