#include <iostream>
#include "String.hpp"
#include <string>

int xml::String::size()
{
  return length;
}
std::ostream &xml::operator<<(std::ostream& stream, const xml::String& s1)
{
  stream << (std::string)s1;
  return stream;
}
xml::String::operator std::string() const
{
  return std::string(contents, length);
}
xml::String::String(const xml::String &)
{

}
xml::String::String()
{
  contents = NULL;
  length = 0;
}
xml::String::String(const char* str, int len)
{
  contents = str;
  length = len;
}
void xml::String::append(int addSize)
{
  length += addSize;
}
bool operator==(const std::string & s1, const xml::String & s2)
{
  return s1 == (std::string)s2;
}

/*
bool xml::operator==(const std::string & s1, const String & s2)
{
  return true;
}
bool xml::operator==(const String & s1, const std::string & s2)
{
  return true;
}
bool xml::operator!=(const std::string & s1, const String & s2)
{
  return true;
}
bool xml::operator!=(const String & s1, const std::string & s2)
{
  return true;
}
//Comparison with C string
bool xml::operator==(const char* s1, const String & s2)
{
  return true;
}
bool xml::operator==(const String & s1, const char * s2)
{
  return true;
}
bool xml::operator!=(const char * s1, const String & s2)
{
  return true;
}
bool xml::operator!=(const String & s1, const char * s2)
{
  return true;
}*/
