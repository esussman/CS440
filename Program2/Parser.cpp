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
            //throw error bad input
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
              cout << "Parent " << *(*nodeStack.top()).elemName << endl;
              nodeStack.top()->children.push_back((Element*)currentNode);
            }
            nodeStack.push((Element*)currentNode);
            tempString = NULL;
            state = inside_body;
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
            delete tempString;
            tempString = NULL;
            state = inside_body;
          }
              break;
        case inside_body:
          resetTempString(doc + i);
          if(isValidTextChar(data))
          {
            (*tempString).append(1);
          }
          if(data == '<')
          {
            state = name_or_namespace;
            //you have the next you need, create an element and add it.
            currentNode = new Element();
            tempString = NULL;
          }
          if(i == sz)
            return root;
          break;
      }
      break;
    }
  }
  return 0;
}
