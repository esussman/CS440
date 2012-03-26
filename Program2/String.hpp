#include <string>

class String {
  public:
    String(const String &);
    //Conversion to stf::string
    operator std::string() const;
    //Assigment.
    String &operator=(const String &);
};
//Comparison with std::string.
bool operator==(const std::string &, const String &);
bool operator==(const String &, const std::string &);
bool operator!=(const std::string &, const String &);
bool operator!=(const String &, const std::string &);
//Comparison with C string
bool operator==(const char*, const String &);
bool operator==(const String &, const char *);
bool operator!=(const char *, const String &);
bool operator!=(const String &, const char *);

std::ostream &operator<<(std::ostream &, const String &);

