#pragma once

#include "GameObject.h"
#include "StaticSolids.h"
#include "SpriteSheet.h"

// Function for parsing a text file of game objects
std::vector<GameObject*> loadObjects(sf::String& fileName);

// Individual object loading functions
Wall* loadWall(std::ifstream& fileStream);
PlayerShield* loadPlayerShield(std::ifstream& fileStream);
Tile* loadTile(std::ifstream& fileStream);