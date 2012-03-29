#include "Element.hpp"
#include <list>

xml::Element::Element()
{
  elemName = NULL;
  elemNameSpace = NULL;
}
xml::Element::~Element()
{
  delete(elemName);
  delete(elemNameSpace);
}
const xml::String& xml::Element::name() const
{
  return *elemName;
}
const xml::String& xml::Element::nmspace() const
{
  return *elemNameSpace;
}
bool xml::Element::is_Element(const Node * n)
{
  return dynamic_cast<const Element*>(n) != 0;
}
const xml::Element *xml::Element::to_Element(const Node *n)
{
  return dynamic_cast<const Element*>(n);
}
const Node *xml::Element::child(size_t i) const
{
  return 0;
}
size_t xml::Element::n_children() const
{
  return children.size();
}
void xml::Element::accept(xml::Visitor *) const
{
}
