#ifndef EVAN_SUSSMAN_TEXT
#define EVAN_SUSSMAN_TEXT

#include "Node.hpp"
#include "String.hpp"
namespace xml {

  class Text : public Node {
    friend class Parser;
    public:
      Text();
      ~Text();
      const String& str() const;
      static bool is_Text(const Node*);
      static const Text *to_Text(const Node *);
      //void accept(Visitor *) const;
    private:
      String *contents;
  };
}
#endif
