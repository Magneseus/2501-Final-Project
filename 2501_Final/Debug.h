#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <string>
#include <iostream>
#include <unordered_set>

class Debug
{
public:
	static void draw(sf::Drawable* ddraw);
	static void print(std::string& str);
	static void print(sf::String& str);

	static bool debugging;
	static std::unordered_set<sf::Drawable*> debugDrawables;

	
};