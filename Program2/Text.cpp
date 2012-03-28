#include "Text.hpp"

const xml::String& xml::Text::str() const
{
  return *contents;
}

bool xml::Text::is_Text(const Node* n)
{
  return dynamic_cast<const Text*>(n) != 0;
}

const xml::Text *xml::Text::to_Text(const Node *n)
{
	return dynamic_cast<const Text*>(n);
}
