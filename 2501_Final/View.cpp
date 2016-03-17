#include "View.h"

#include <iostream>

View::View(Model* m)
	: model(m),
	WINDOW_WIDTH(800),
	WINDOW_HEIGHT(800),
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Pirates...?"),
	showFPS(true)
{
	//window.setFramerateLimit(60);

	/*
	temp = new AnimatedSprite();

	std::vector<sf::Texture*> files;

	a = new sf::Texture();
	b = new sf::Texture();
	c = new sf::Texture();
	d = new sf::Texture();
	a->loadFromFile("img/test_1.png");
	b->loadFromFile("img/test_2.png");
	c->loadFromFile("img/test_3.png");
	d->loadFromFile("img/test_4.png");

	files.push_back(a);
	files.push_back(b);
	files.push_back(c);
	files.push_back(d);

	temp->create(files, 10);

	temp->setPosition(100, 100);
	*/

	// Random hangar tiles
	hangar_tile.loadFromFile("img/tile_64.png");
	hangar_tile.setRepeated(true);

	hangar.setTexture(hangar_tile);
	hangar.setTextureRect(sf::IntRect(0, 0, 64 * 6, 64 * 6));
	hangar.setOrigin(64 * 3, 64 * 3);
	hangar.setPosition(400, 400);

	// Load some fonts
	if (!Global::niceFont.loadFromFile("fonts/FiraSans-Regular.otf"))
	{
		std::cout << "Nice font not loaded!\n";
	}
	fpsText.setFont(Global::niceFont);

	window.setKeyRepeatEnabled(false);	// prevent player from spamming keys accidentally
}

View::~View()
{
	
}

void View::render()
{
	window.clear();

	window.draw(hangar, globalTransform);

	for (auto it = drawables.begin(); it != drawables.end(); )
	{
		// Check if it needs to be removed
		if ((*it)->removeFunc())
		{
			(*it)->andType(0b101);
			it = drawables.erase(it);
		}
		else
		{
			if (*it != NULL)
				window.draw(**it, globalTransform);
			++it;
		}

	}

	// display FPS
	if (showFPS)
	{
		float total = 0;
		for (auto it = fps.begin(); it != fps.end(); ++it)
			total += *it;

		total /= fps.size();
		
		int FPS = 1.0f / total;
		std::stringstream fpsString;
		fpsString << "FPS: " << FPS;

		fpsText.setString(fpsString.str());
		fpsText.setCharacterSize(20);
		fpsText.setColor(sf::Color::White);
		fpsText.setPosition(sf::Vector2f(0, 0));
		window.draw(fpsText);
	}
	
	window.display();
}

/*
	This function simply adds a drawable object to the list to be rendered.
*/
void View::addDrawable(Drawable* d)
{
	// If we have a null pointer, don't add it to the list
	if (!d) return;

	drawables.push_back(d);
}

/*
	This function removes a drawable object from our render list.

	Return:
	 - true: The object was stored in our list, and was flagged to be removed
	 - false: The object wasn't stored in our list, not flagged for removal
*/
bool View::delDrawable(Drawable* d)
{
	bool contains = false;
	for (auto it = drawables.begin(); it != drawables.end() && !contains; it++)
	{
		// Object was found
		if (*it == d)
		{
			contains = true;
			break;
		}
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
	{
		d->deleteObject();
		d->andType(0b101);
	}

	// Tell them if we had an object stored and flagged it
	return contains;
}

bool View::remDrawable(Drawable* u)
{
	for (auto it = drawables.begin(); it != drawables.end(); it++)
	{
		// Object was found
		if (*it == u)
		{
			drawables.erase(it);
			return true;
		}
	}

	return false;
}

/*
	This function sets the global transform object. Will be applied to all Drawables.
*/
void View::setTransform(const sf::Transform& _trans)
{
	globalTransform = _trans;
}

/*
	Return transforms.
*/
sf::Transform View::getTransform()
{
	return globalTransform;
}

void View::addFPS(const sf::Time& timeForFrame)
{
	fps.push_back(timeForFrame.asSeconds());

	if (fps.size() > 20)
		fps.pop_front();
}