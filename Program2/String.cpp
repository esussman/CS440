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
bool xml::String::operator==(const String& s1) const
{
  return strncmp(contents, s1.contents, length) == 0;
}
bool xml::String::operator<(const String& s1) const
{
  return strncmp(contents, s1.contents, length);
}
bool xml::String::operator!=(const String& s1) const
{
  return strncmp(contents, s1.contents, length) != 0;
}

xml::String::operator std::string() const
{
  return std::string(contents, length);
}
xml::String::String(const xml::String & s1)
{
  contents = s1.contents;
  length = s1.length;
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
bool xml::operator==(const String & s1, const char * s2)
{
  return strncmp(s1.contents, s2, s1.length);
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
