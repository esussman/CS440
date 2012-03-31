#include "Element.hpp"
#include <list>

xml::Element::Element()
{
  elemName = NULL;
  //elemNameSpace = new String("",0);
}
xml::Element::~Element()
{
  delete elemName;
  //delete(elemNameSpace);
  for(std::list<Node*>::const_iterator it = children.begin(); it != children.end(); it++)
    delete(*it);
}
const xml::String& xml::Element::name() const
{
  return *elemName;
}
const xml::String& xml::Element::nmspace() const
{
//  return *elemNameSpace;
  return *elemName;
}
bool xml::Element::is_Element(const Node * n)
{
  return dynamic_cast<const Element*>(n) != 0;
}
const xml::Element *xml::Element::to_Element(const Node *n)
{
  return dynamic_cast<const Element*>(n);
}
const xml::Text *xml::Element::to_Text(const Node* n)
{
  return dynamic_cast<const Text*>(n);
}
const Node *xml::Element::child(size_t i) const
{
  std::list<Node*>::const_iterator it = children.begin();
  std::advance(it, i);
  return *it;
}
size_t xml::Element::n_children() const
{
  return children.size();
}
void xml::Element::accept(xml::Visitor * v) const
{
  Element e = *this;
  v->start_element_visit(e);
  for(std::list<Node*>::const_iterator it = children.begin(); it != children.end(); it++)
  {
    if(Element::is_Element(*it))
    {
      dynamic_cast<const Element*>(*it)->accept(v);
    }
    if(Text::is_Text(*it))
    {
      v->visit_text(*dynamic_cast<const Text*>(*it));
    }
  }
  // v->start_element_visit(e);
  // for(unsigned int i = 0; i < e.n_children(); i++)
  // {
    // if(Element::is_Element(e.child(i)))
    // {
      // Element child = *dynamic_cast<const Element*>(e.child(i));
      // child.accept(v);
    // }
    // else if(Text::is_Text(e.child(i)))
    // {
      // v->visit_text(*dynamic_cast<const Text*>(e.child(i)));
    // }
  // }
  v->end_element_visit(e);
}
