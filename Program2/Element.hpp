#ifndef EVAN_SUSSMAN_ELEMENT
#define EVAN_SUSSMAN_ELEMENT
#include <list>
#include "String.hpp"
#include "Node.hpp"
#include "Text.hpp"

namespace xml {
  class Visitor;

  class Element : public Node {
    friend class Parser;
    public:
      Element();
      ~Element();
      const String &name() const;
      const String &nmspace() const;
      const String &nmspaceURL() const;
      size_t n_children() const;
      const Node *child(size_t) const;
      void accept(Visitor *) const;
      //use RTTI
      static bool is_Element(const Node *);
      static const Element *to_Element(const Node *);
      static const Text *to_Text(const Node *);
    private:
      std::list<Node *> children;
      String *elemName;
      const String *elemNameSpace;
      String *elemNameSpaceURL;
  };
}

  #include "Visitor.hpp"
#endif
