#ifndef EVAN_SUSSMAN_VISITOR
#define EVAN_SUSSMAN_VISITOR

#include "Element.hpp"
#include "Text.hpp"

namespace xml {

  class Visitor {
    public:
      virtual void start_element_visit(const xml::Element &) = 0;
      virtual void end_element_visit(const xml::Element &) = 0;
      virtual void visit_text(const Text &) = 0;
  };
}
#endif

