#include "Parser.hpp"
#include "String.hpp"
#include "Text.hpp"
#include <iostream>
#include <stack>
#include <string>

using namespace std;

xml::Parser::Parser()
{
  state = start;
  tempString = NULL;
  root = NULL;
}
void xml::Parser::saveText(Text *text)
{
  text->contents = tempString;
  if(nodeStack.size() > 0)
    nodeStack.top()->children.push_back(text);
  tempString = NULL;
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
  return data != '<' && data != '>';
}
const xml::Element* xml::Parser::parse(const char*doc, size_t sz)
{
  Node* currentNode = new Element();
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
            root = dynamic_cast<Element*>(currentNode);
            state = name_or_namespace;
          }
          else
          {
            exit(9);
          }
            break;
        case name_or_namespace:
          resetTempString(doc+i);
          if(isspace(data) && tempString != NULL)
          {
          }
          else if(data == '/')
          {
            //close tag
            tempString = NULL;
            state = close_name_or_namespace;
          }
          else if(data == '>')
          {
            dynamic_cast<Element*>(currentNode)->elemName = tempString;
            //add the element to the children of the current top element of the stack.
            if(nodeStack.size() != 0){
              nodeStack.top()->children.push_back((Element*)currentNode);
            }
            nodeStack.push((Element*)currentNode);
            tempString = NULL;
            state = inside_body;
            continue;
          }
          else if(isValidNameChar(data))
          {
            (*tempString).append(1);
          }
              break;
        case close_name_or_namespace:
          resetTempString(doc + i);
          if(isValidNameChar(data))
          {
            (*tempString).append(1);
          }
          if(data == '>')
          {
              //Good name
            nodeStack.pop();
            tempString = NULL;
            state = inside_body;
          }
              break;
        case inside_text:
          resetTempString(doc + i);
          if( data == '<')
          {
            //want to save the text.
            //switch to inside_body and let that switch to name
            saveText((Text*)currentNode);
            state = inside_body;
            continue;
          }
          else if(isValidTextChar(data))
          {
            (*tempString).append(1);
          }
          else
            exit(9);
          break;
        case inside_body:

          if(i == sz)
            return root;
          else if(data == '<')
          {
            //must want to deal with the name
            //delete currentNode;
            currentNode = new Element();
            state = name_or_namespace;
          }
          else if(data == '>')
          {
            //must be looking at text
            currentNode = new Text();
            state = inside_text;
            //continue;
          }
          break;
      }
      break;
    }
  }
  return root;
}
