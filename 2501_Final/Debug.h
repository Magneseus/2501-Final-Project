#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <unordered_set>

class Debug
{
public:
	static std::unordered_set<sf::Drawable*> debugDrawables;
	static void draw(sf::Drawable* ddraw);
	
};