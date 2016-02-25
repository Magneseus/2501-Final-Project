#include "Controller.h"

Controller::Controller(Model* m, View* v)
	: model(m),
	view(v),
	GSTATE(GSTATES::GAME)
{

}

Controller::~Controller()
{
	
}

void Controller::input()
{
	// EVENT-BASED INPUT
	sf::Event e;
	while (view->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::Escape)
				view->window.close();
			break;
		case sf::Event::Closed:
			view->window.close();
			break;
		}
	}

	// REAL-TIME INPUT

}

void Controller::gameController()
{
	// Check all game objects
	for (auto it = gameObjects.begin(); it != gameObjects.end(); )
	{
		if ((*it)->removeFunc() && (*it)->isNone())
		{
			// Delete the memory for this game object, as all lists have removed it now
			delete (*it);
			(*it) = NULL;

			it = gameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

/*
	This function adds a GameObject instance to the world. It will then add it to any applicable
	lists (the drawables in View, or the Updatables in Model, etc.)
*/
void Controller::addObject(GameObject* newObject)
{
	// If we have a null pointer, don't add it to the list
	if (!newObject) return;

	// Add it to the master list
	gameObjects.push_back(newObject);

	// Add it to the appropriate lists
	if (newObject->isUpdatable())
		model->addUpdatable(dynamic_cast<Updatable*>(newObject));
	if (newObject->isDrawable())
		view->addDrawable(dynamic_cast<Drawable*>(newObject));
	if (newObject->isCollidable())
		model->addCollidable(dynamic_cast<Collidable*>(newObject));
}

/*
	This function removes an object from the master lists and all sub-lists.
*/
bool Controller::delObject(GameObject* delObj)
{
	if (!delObj) return false;

	bool contains = false;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (*it == delObj)
		{
			contains = true;
			break;
		}
	}

	if (contains)
	{
		delObj->deleteObject();
	}

	return contains;
}