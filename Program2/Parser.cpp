#include "Parser.hpp"
#include "ParserException.hpp"
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
void xml::Parser::saveElement(Element* currentNode)
{
  if(currentNode->elemNameSpace == NULL)
  {
    currentNode->elemNameSpace = new String();
  }
  if(nodeStack.size() != 0){
    nodeStack.top()->children.push_back((Element*)currentNode);
  }
  nodeStack.push((Element*)currentNode);
  tempString = NULL;
}
void xml::Parser::saveText(Text *text)
{
  dynamic_cast<Text*>(text)->contents = tempString;
  if(nodeStack.size() > 0)
    nodeStack.top()->children.push_back((Text*)text);
  tempString = NULL;
}
bool xml::Parser::isValidAddressChar(const char data)
{
  return data != '"' && !isspace(data);
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
    if(data == EOF)
      break;

    while(true)
    {
      try
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
              throw ParserError("Invalid Text before root tag.");
            }
              break;
          case type_of_tag:
              if(data == '/')
              {
                state = close_name_or_namespace;
              }
              else
              {
                state = name_or_namespace;
                continue;
              }
              break;
          case name_or_namespace:
            resetTempString(doc+i);
            if(isspace(data) && tempString->size() == 0)
            {
              throw ParserError("No whitespace allowed before element name");
            }
            else if(data == ':' && tempString->size() != 0)
            {
              //previous text must be namespace
              dynamic_cast<Element*>(currentNode)->elemNameSpace = tempString;
              tempString = NULL;
              state = must_be_name;
            }
            else if(isspace(data))
            {
              //maybe continue?
              state = tag_name_clear_ws;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else if(data == '>')
            {
              dynamic_cast<Element*>(currentNode)->elemName = tempString;
              //add the element to the children of the current top element of the stack.
              saveElement((Element*)currentNode);
              state = inside_body;
            }
            else
            {
              throw ParserError("Unexpected input");
            }
                break;
          case must_be_name:
            resetTempString(doc+i);
            if(data == '>')
            {
              dynamic_cast<Element*>(currentNode)->elemName = tempString;
              saveElement((Element*)currentNode);
              state = inside_body;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else if(isspace(data) && tempString->size() == 0)
            {
              throw ParserError("No whitespace between namespace and name");
            }
            else if(isspace(data) && tempString->size() > 0)
            {
              //go to clear ws name
              state = tag_name_clear_ws;
            }
                break;
          case tag_name_clear_ws:
            if(data == '>')
            {
              //save the element
              dynamic_cast<Element*>(currentNode)->elemName = tempString;
              saveElement((Element*)currentNode);
              state = inside_body;
            }
            else if(isspace(data))
            {
              //dont do anything
            }
            else
            {
              //must be xmlns must save element
              dynamic_cast<Element*>(currentNode)->elemName = tempString;
              saveElement((Element*)currentNode);
              state = check_xmlns;
              continue;
            }
            break;
          case check_xmlns:
            resetTempString(doc + i);
            if(data == ':' && *tempString == String("xmlns", 5))
            {
              delete tempString;
              tempString = NULL;
              state = def_namespace_name;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else
              throw ParserError("invalid xml");
            break;
          case def_namespace_name:
            resetTempString(doc + i);
            if(data == '=' && *tempString != String("",0))
            {
              //namespace name = tempString;
              //move to quote state
              delete tempString;
              tempString = NULL;
              state = namespace_quote;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else
            {
              throw ParserError("invalid xml found");
            }
            break;
          case namespace_quote:
            if(data == '"') {
              state = namespace_definition;
            }
            else
              throw ParserError("invald namespace definition, must start with \" ");
            break;
          case namespace_definition:
            resetTempString(doc + i);
            if(data == '"' && tempString != NULL)
            {
              //save definition
              //go to end_namespace_definition
              delete tempString;
              tempString = NULL;
              state = end_namespace_definition_ws;
            }
            else if(isValidAddressChar(data))
            {
              (*tempString).append(1);
            }
            else
              throw ParserError("invalid xml found");
            break;
          case end_namespace_definition_ws:
            if(isspace(data))
            {
              //do nothing
            }
            else if(isValidNameChar(data))
            {
              state = check_xmlns;
              continue;
            }
            else if(data == '>')
            {
              state = inside_body;
            }
            else
              throw ParserError("invalid xml input");
            break;
          case close_name_or_namespace:
            resetTempString(doc + i);
            if(isspace(data) && tempString->size() == 0)
            {
              throw ParserError("No whitespace allowed before element name");
            }
            else if(isspace(data) && tempString->size() > 0)
            {
              state = close_tag_name_clear_ws;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else if(data == ':' && nodeStack.top()->nmspace() == *tempString)
            {
              delete tempString;
              tempString = NULL;
              state = close_must_be_name;
            }
            else if(data == '>' && nodeStack.top()->name() == *tempString && nodeStack.top()->nmspace() == String("",0))
            {
                //Good name
              nodeStack.pop();
              delete currentNode;
              currentNode = NULL;
              delete tempString;
              tempString = NULL;
              state = inside_body;
            }
            else
            {
              throw ParserError("Unexpected input");
            }
                break;
          case close_must_be_name:
            resetTempString(doc+i);
            if(data == '>' && nodeStack.top()->name() == *tempString)
            {
              //check if the names are equal
              nodeStack.pop();
              delete currentNode;
              currentNode = NULL;
              delete tempString;
              tempString = NULL;
              state = inside_body;
            }
            else if(isValidNameChar(data))
            {
              (*tempString).append(1);
            }
            else if(isspace(data) && tempString->size() == 0)
            {
              throw ParserError("No whitespace between namespace and name");
            }
            else if(isspace(data) && tempString->size() > 0)
            {
              //go to get close_ws_endtag
              state = close_tag_name_clear_ws;
            }
            else
            {
               throw ParserError("Names dont match!");
            }
            break;
          case close_tag_name_clear_ws:
            if(data == '>')
            {
              nodeStack.pop();
              delete currentNode;
              currentNode = NULL;
              delete tempString;
              tempString = NULL;
              state = inside_body;
            }
            else if(isspace(data))
            {
              //dont do anything
            }
            else
            {
              throw ParserError("invald text after space");
            }
            break;
          case inside_text:
            if(nodeStack.size() == 0 && !isspace(data))
              throw ParserError("Text outside of tags!");
            resetTempString(doc + i);
            if( data == '<')
            {
              saveText((Text*)currentNode);
              state = inside_body;
              continue;
            }
            else if(isValidTextChar(data))
            {
              (*tempString).append(1);
            }
            else
              throw ParserError("Unexpected input");
            break;

          case inside_body:
            if(i == sz)
              return root;
            else if(data == '<')
            {
              //must want to deal with the name
              currentNode = new Element();
              state = type_of_tag;
           }
            else
            {
              //must be looking at text
              if(nodeStack.size() == 0 && isspace(data))
                break;
              currentNode = new Text();
              state = inside_text;
              continue;
            }
            break;
        }
      }
      catch(ParserError e)
      {
        cout << e.what() << endl;
        exit(1);
      } //end try, obviously
      break;
    } //end while
  } //end for
  try{
  if(nodeStack.size() !=  0)
    throw ParserError("unclosed tag");
  }
  catch(ParserError e)
  {
        cout << e.what() << endl;
        exit(1);
  }
  delete tempString;

  return root;
}

/*
 * FIXME:: If first n characters are the same of start and end tag
 * it will match even if end tag has remaining characters.
 *
 */

