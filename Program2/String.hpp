#ifndef EVAN_SUSSMAN_STRING
#define EVAN_SUSSMAN_STRING
#include <string>
namespace xml{

  class String {
    public:
      //Copy constructor
      String(const String &);
      String();
      String(const char*, int);
      void append(int);
      int size();
      //Conversion to stf::string
      operator std::string() const;
      //Assigment.
      String &operator=(const String &);

    private:
      const char* contents;
      int length;
  };
  //Comparison with std::string
  bool operator==(const std::string &, const xml::String &);
  bool operator==(const String &, const std::string &);
  bool operator!=(const std::string &, const String &);
  bool operator!=(const String &, const std::string &);
  //Comparison with C string
  bool operator==(const char*, const String &);
  bool operator==(const String &, const char *);
  bool operator!=(const char *, const String &);
  bool operator!=(const String &, const char *);
//Comparison with std::string.
  std::ostream &operator<<(std::ostream &, const String &);

}
#endif
