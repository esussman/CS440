#include <iostream>
#include "String.hpp"
#include <string>

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