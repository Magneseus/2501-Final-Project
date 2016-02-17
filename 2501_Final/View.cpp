#include "View.h"

View::View(Model* m)
	: model(m),
	WINDOW_WIDTH(720),
	WINDOW_HEIGHT(480),
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Pirates...?")
{
	
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
			it = drawables.erase(it);
		}
		else
		{
			window.draw(**it);
			++it;
		}

	}

	window.display();
}

/*
	This function simply adds a drawable object to the list to be rendered.
*/
void View::addDrawable(Drawable* d)
{
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
			contains = true;
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
		d->deleteObject();

	// Tell them if we had an object stored and flagged it
	return contains;
}