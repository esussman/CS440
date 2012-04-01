#include "Text.hpp"

xml::Text::~Text()
{
  delete contents;
}
xml::Text::Text()
{
  contents = NULL;
}

const xml::String& xml::Text::str() const
{
  return *contents;
}

bool xml::Text::is_Text(const Node* n)
{
  return dynamic_cast<const Text*>(n) != NULL;
}

const xml::Text *xml::Text::to_Text(const Node *n)
{
	return dynamic_cast<const Text*>(n);
}
