#include "View.h"

#include <iostream>

View::View(Model* m)
	: model(m),
	WINDOW_WIDTH(720),
	WINDOW_HEIGHT(480),
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Pirates...?")
{
	window.setFramerateLimit(60);

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
}

View::~View()
{
	
}

void View::render()
{

	window.clear();

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
				window.draw(**it);
			++it;
		}

	}

	temp->setTexture(*(temp->getTexture()));
	temp->update();
	window.draw(*temp);

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