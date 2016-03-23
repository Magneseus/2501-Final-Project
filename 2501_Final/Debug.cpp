#include "Debug.h"

std::unordered_set<sf::Drawable*> Debug::debugDrawables;

void Debug::draw(sf::Drawable* ddraw)
{
	debugDrawables.insert(ddraw);
}