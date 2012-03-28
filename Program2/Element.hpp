#ifndef EVAN_SUSSMAN_ELEMENT
#define EVAN_SUSSMAN_ELEMENT
#include <list>
#include "String.hpp"
#include "Node.hpp"

namespace xml {
  class Visitor;

  class Element : public Node {
    public:
      const String &name() const;
      const String &nmspace() const;
      size_t n_children() const;
      const Node *child(size_t) const;
      void accept(Visitor *) const;
      //use RTTI
      static bool is_Element(const Node *);
      static const Element *to_Element(const Node *);
    private:
      std::list<Node *> children;
      const String elemName;
      const String elemNameSpace;
  };

}
#endif
