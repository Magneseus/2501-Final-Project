#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <unordered_map>
#include <fstream>
#include <sstream>

#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_iterators.hpp"

class SpriteSheet
{
public:
	SpriteSheet();
	SpriteSheet(const sf::String& fileName);
	~SpriteSheet();

	bool loadFile(const sf::String& fileName);
	sf::Texture* getTex(const sf::String& texName);
	sf::Vector2i getTexPivot(const sf::String& texName);

private:
	// Small struct to hold both the texture and coordinates for the map
	struct texStruct
	{
		sf::Texture* tex;
		sf::IntRect texCoords;
		sf::Vector2i pivot;
	};

	sf::String sheetName;
	sf::Image* sheetImage;
	std::unordered_map<std::string, texStruct> texMap;
};