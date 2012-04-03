#include "Element.hpp"
#include <list>

xml::Element::Element()
{
  elemName = NULL;
  elemNameSpace = NULL;
  elemNameSpaceURL = NULL;
}
xml::Element::~Element()
{
  delete elemName;
  delete elemNameSpace;
  delete elemNameSpaceURL;
  for(std::list<Node*>::const_iterator it = children.begin(); it != children.end(); it++)
    delete *it;
}
const xml::String& xml::Element::nmspaceURL() const
{
  return *elemNameSpaceURL;
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
  return dynamic_cast<const Element*>(n) != NULL;
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
  // v->start_element_visit(*this);
  // for(std::list<Node*>::const_iterator it = children.begin(); it != children.end(); it++)
  // {
    // if(Element::is_Element(*it))
    // {
      // dynamic_cast<const Element*>(*it)->accept(v);
    // }
    // if(Text::is_Text(*it))
    // {
      // v->visit_text(*dynamic_cast<const Text*>(*it));
    // }
  // }
  v->start_element_visit(*this);
  for(unsigned int i = 0; i < (*this).n_children(); i++)
  {
    if(Element::is_Element((*this).child(i)))
    {
      dynamic_cast<const Element*>((*this).child(i))->accept(v);

    }
    else if(Text::is_Text((*this).child(i)))
    {
      v->visit_text(*dynamic_cast<const Text*>((*this).child(i)));
    }
  }
  v->end_element_visit(*this);
}
