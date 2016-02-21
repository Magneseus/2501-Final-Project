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


sf::Texture* SpriteSheet::getTex(const sf::String& texName)
{
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
	This function will attempt to load in an image designated by fileName, as
	well as it's XML counterpart (must be the same filename but with a .xml suffix).

	It will load in all the texture coordinates into the texMap map.
 */
bool SpriteSheet::loadFile(const sf::String& fileName)
{
	// Try to load and mask the image
	if (!sheetImage->loadFromFile(fileName))
	{
		sf::err() << "Failed to load spritesheet file: " << fileName.toAnsiString() << std::endl;
		sheetImage = NULL;

		return false;
	}
	else
	{
		sheetImage->createMaskFromColor(sf::Color::White);
	}

	// Get the XML name
	sf::String sheetNameXML = sheetName;
	sheetNameXML.substring(0, sheetNameXML.getSize() - 3);
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
	for (auto node = ss_rootNode->first_node("SubTexture"); node; node = node->next_sibling())
	{
		std::string key = node->first_attribute("name")->value();
		std::string xstr = node->first_attribute("x")->value();
		std::string ystr = node->first_attribute("y")->value();
		std::string wstr = node->first_attribute("width")->value();
		std::string hstr = node->first_attribute("height")->value();

		int x, y, w, h;
		if (!(std::stringstream(xstr) >> x)) x = 0;
		if (!(std::stringstream(ystr) >> y)) y = 0;
		if (!(std::stringstream(wstr) >> w)) w = 0;
		if (!(std::stringstream(hstr) >> h)) h = 0;

		// Store the new info
		texStruct newTexStruct;
		newTexStruct.texCoords = sf::IntRect(x, y, w, h);
		newTexStruct.tex = NULL;

		texMap[key] = newTexStruct;
	}

	return true;
}