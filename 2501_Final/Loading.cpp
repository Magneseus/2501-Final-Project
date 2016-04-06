#include "Loading.h"

/* This function will load a file of GameObject information and return the created objects
*
* File format:
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* NUMBER_OF_OBJECTS
*
* w WALL_X WALL_Y WALL_W WALL_H WALL_ROT WALL_TEXNAME
* s SHIELD_X SHIELD_Y SHIELD_W SHIELD_H SHIELD_ROT SHIELD_TEXNAME
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
std::vector<GameObject*> loadObjects(sf::String& fileName)
{
	std::vector<GameObject*> objects;

	// Load the file
	std::ifstream FILE(fileName.toAnsiString());

	if (FILE.is_open())
	{
		// Get # walls
		int nObjs = 0;
		FILE >> nObjs;

		// Read in the information for the walls
		for (int i = 0; i < nObjs; ++i)
		{
			GameObject* obj = NULL;
			char objType = '\0';

			// Get the object type
			FILE >> objType;

			switch (objType)
			{
			default:
				break;

			// Walls
			case 'w':
			case 'W':
				obj = loadWall(FILE);
				break;

			// Player Shield
			case 's':
			case 'S':
				obj = loadPlayerShield(FILE);
				break;

			// Tiles
			case 'f':
			case 'F':
				obj = loadTile(FILE);
				break;

			// Turrets
			case 't':
			case 'T':
				
				break;
			}


			if (obj != NULL)
				objects.push_back(obj);
		}
	}

	return objects;
}





/////////////////////////////////////////////////////////////////////////
//              Individual Object Loading Functions                    //
/////////////////////////////////////////////////////////////////////////


// Walls
Wall* loadWall(std::ifstream& fileStream)
{
	int WX = 0, WY = 0;
	int WW = 0, WH = 0;
	int WR = 0;
	std::string WT;

	// X & Y
	fileStream >> WX;
	fileStream >> WY;

	// Width & Height
	fileStream >> WW;
	fileStream >> WH;

	// Rotation
	fileStream >> WR;

	// Texture
	fileStream >> WT;
	sf::Texture* wallTex = Global::globalSpriteSheet->getTex(sf::String(WT));
	wallTex->setRepeated(true);

	// Make the new wall and add it to the list
	Wall* w = new Wall(
		vec::Vector2(-WW / 2, -WH / 2),
		vec::Vector2(WW / 2, WH / 2),
		wallTex);
	w->setPosition(vec::Vector2(WX, WY));
	w->setRotation(WR);

	if (Global::DEBUG)
		w->setTag(sf::String("Obj_T"));

	return w;
}

// Player Shield
PlayerShield* loadPlayerShield(std::ifstream& fileStream)
{
	int SX = 0, SY = 0;
	int SW = 0, SH = 0;
	int SR = 0;
	std::string ST;

	// X & Y
	fileStream >> SX;
	fileStream >> SY;

	// Width & Height
	fileStream >> SW;
	fileStream >> SH;

	// Rotation
	fileStream >> SR;

	// Texture
	fileStream >> ST;
	sf::Texture* shieldTex = Global::globalSpriteSheet->getTex(sf::String(ST));
	shieldTex->setRepeated(true);

	// Make the new PlayerShield and add it to the list
	PlayerShield* s = new PlayerShield(
		vec::Vector2(-SW / 2, -SH / 2),
		vec::Vector2(SW / 2, SH / 2),
		shieldTex);
	s->setPosition(vec::Vector2(SX, SY));
	s->setRotation(SR);

	if (Global::DEBUG)
		s->setTag(sf::String("Obj_T"));

	return s;
}

// Loading tiles
Tile* loadTile(std::ifstream& fileStream)
{
	int TX = 0, TY = 0;
	int COUNT = 0;
	std::string TEXTURE;

	// X & Y
	fileStream >> TX;
	fileStream >> TY;
	
	// Texture
	fileStream >> TEXTURE;

	sf::Texture* tileTex = Global::globalSpriteSheet->getTex(sf::String(TEXTURE));

	// Number of points
	fileStream >> COUNT;

	std::vector<vec::Vector2> POINTS;

	for (int i = 0; i < COUNT; ++i)
	{
		std::cout << "TEST";

		float PX = 0.0f, PY = 0.0f;

		fileStream >> PX;
		fileStream >> PY;

		POINTS.push_back(vec::Vector2(PX, PY));
	}

	Tile* t = new Tile(tileTex, POINTS, vec::Vector2(TX, TY));

	if (Global::DEBUG)
		t->setTag(sf::String("Obj_T"));

	return t;
}