#include "Parser.hpp"
#include "String.hpp"
#include "Text.hpp"

xml::Parser::Parser()
{
  state = start;
  tempString = NULL;
  root = NULL;
}
void xml::Parser::resetTempString(const char* string)
{
  if(tempString == NULL)
    tempString = new String(string,0);
}
bool xml::Parser::isValidNameChar(const char data)
{
  return isalnum(data) || data == '_';
}
bool xml::Parser::isValidTextChar(const char data)
{
  return data != '<';
}
const xml::Element* xml::Parser::parse(const char*doc, size_t sz)
{
  root = new Element();
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
            root->elemName = tempString;
          }
          else if(data == '/')
          {
            //close tag
            state = close_name_or_namespace;
          }
          else if(data == ':')
          {
            //the accum is namespace
          }
          else if(data == '>')
          {
            root->elemName = tempString;
            state = inside_body;
//             Node *innerText = new Text();
          }
          else if(isValidNameChar(data))
          {
            (*tempString).append(1);
          }
              break;
        case close_name_or_namespace:
              break;
        case inside_body:
          resetTempString(doc + i);
          if(isValidTextChar(data))
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
