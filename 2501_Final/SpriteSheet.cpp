#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
	: sheetName("")
{

}

SpriteSheet::SpriteSheet(const sf::String& fileName)
	: sheetName(fileName)
{
	loadFile(fileName);
}

SpriteSheet::~SpriteSheet()
{
	// Delete all the Textures in the texMap
	for (auto it = texMap.begin(); it != texMap.end(); it++)
	{
		if (it->second.tex != NULL)
		{
			delete it->second.tex;
			it->second.tex = NULL;
		}
	}
	texMap.clear();

	// Delete the master texture
	delete sheetImage;
}


/*
	Returns a pointer to a texture loaded from the spritesheet.

	If the texture doesn't exist, but the key is there then the
	texture will be loaded in and returned.

	If the texture doesn't exist and there is no key then NULL
	will be returned.

	Parameters:
		- texName : Key to search for (texture file name).
	Return:
		- pointer to texture, or NULL if key is invalid
*/
sf::Texture* SpriteSheet::getTex(const sf::String& texName)
{
	// Check to see if the key exists
	if (texMap.count(texName) <= 0)
		return NULL;

	texStruct& val = texMap[texName];

	// Check if the texture doesn't exist
	if (val.tex == NULL)
	{
		val.tex = new sf::Texture();
		val.tex->loadFromImage(*sheetImage, val.texCoords);
	}

	return val.tex;
}

/*
	Returns a vector representing the pivot point (origin) of the texture.

	If the key doesn't exist, a vector of [-1, -1] will be returned.

	Parameters:
		- texName : Key to search for (texture file name).
	Return:
		- copy of pivot vector, or [-1, -1] if key is invalid
*/
sf::Vector2i SpriteSheet::getTexPivot(const sf::String& texName)
{
	// Check to see if the key exists
	if (texMap.count(texName) <= 0)
		return sf::Vector2i(-1, -1);

	texStruct& val = texMap[texName];

	return val.pivot;
}

/*
	This function will attempt to load in an image designated by fileName, as
	well as it's XML counterpart (must be the same filename but with a .xml suffix).

	It will load in all the texture coordinates into the texMap map.
 */
bool SpriteSheet::loadFile(const sf::String& fileName)
{
	// Try to load and mask the image

	sheetImage = new sf::Image();
	if ( !(sheetImage->loadFromFile(fileName)) )
	{
		sf::err() << "Failed to load spritesheet file: " << fileName.toAnsiString() << std::endl;
		delete sheetImage;
		sheetImage = NULL;

		return false;
	}
	else
	{
		sheetImage->createMaskFromColor(sf::Color::White);
	}

	// Get the XML name
	sf::String sheetNameXML = sheetName;
	sheetNameXML = sheetNameXML.substring(0, sheetNameXML.getSize() - 4);
	sheetNameXML += ".xml";

	// Now parse the spritesheet's XML file for the tex coordinates
	rapidxml::xml_document<> ss_doc;
	rapidxml::xml_node<> * ss_rootNode;

	// Read the XML file into a vector
	std::ifstream ssDoc(sheetNameXML.toAnsiString());
	std::vector<char> buf((std::istreambuf_iterator<char>(ssDoc)), std::istreambuf_iterator<char>());
	buf.push_back('\0');

	ss_doc.parse<0>(&buf[0]);
	ss_rootNode = ss_doc.first_node("TextureAtlas");

	// Parse the XML tree
	for (auto node = ss_rootNode->first_node("sprite"); node; node = node->next_sibling())
	{
		std::string key = node->first_attribute("n")->value();
		std::string xstr = node->first_attribute("x")->value();
		std::string ystr = node->first_attribute("y")->value();
		std::string wstr = node->first_attribute("w")->value();
		std::string hstr = node->first_attribute("h")->value();
		std::string pxstr = node->first_attribute("pX")->value();
		std::string pystr = node->first_attribute("pY")->value();

		int x, y, w, h;
		float px, py;
		if (!(std::stringstream(xstr) >> x)) x = 0;
		if (!(std::stringstream(ystr) >> y)) y = 0;
		if (!(std::stringstream(wstr) >> w)) w = 0;
		if (!(std::stringstream(hstr) >> h)) h = 0;
		if (!(std::stringstream(pxstr) >> px)) px = 0;
		if (!(std::stringstream(pystr) >> py)) py = 0;

		// Store the new info
		texStruct newTexStruct;
		newTexStruct.texCoords = sf::IntRect(x, y, w, h);
		newTexStruct.pivot = sf::Vector2i(px*w, py*h);
		newTexStruct.tex = NULL;

		texMap[key] = newTexStruct;
	}

	ssDoc.close();

	return true;
}