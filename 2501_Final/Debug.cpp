#include "Debug.h"

bool Debug::debugging;
std::unordered_set<sf::Drawable*> Debug::debugDrawables;

void Debug::draw(sf::Drawable* ddraw)
{
	if (debugging)
		debugDrawables.insert(ddraw);
}

void Debug::print(std::string& str)
{
	if (debugging)
		std::cout << str << std::endl;
}

void Debug::print(sf::String& str)
{
	if (debugging)
		std::cout << str.toAnsiString() << std::endl;
}