#include "Controller.h"

Controller::Controller(Model* m, View* v)
	: model(m),
	view(v),
	GSTATE(GSTATES::GAME)
{
	initObjects();
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

	// Set the static mouse coordinates
	Global::mouseWindowCoords = sf::Mouse::getPosition(view->window);
}

void Controller::gameController()
{
	// Set the view's global transform
	sf::Transform playerPos;
	playerPos.translate(-(p->getPosition()).getSfVec());
	playerPos.translate(view->WINDOW_WIDTH / 2, view->WINDOW_HEIGHT / 2);

	view->setTransform(playerPos);

	// Check the static list for objects to add
	for (auto it = GameObject::staticGameObjects.begin(); it != GameObject::staticGameObjects.end(); ++it)
	{
		addObject(*it);
	}
	GameObject::staticGameObjects.clear();

	// Check the static list for objects to delete
	for (auto it = GameObject::staticGameObjectsDel.begin(); it != GameObject::staticGameObjectsDel.end(); ++it)
	{
		delObject(*it);
	}
	GameObject::staticGameObjectsDel.clear();

	// Check the static list for objects to remove
	for (auto it = GameObject::staticGameObjectsRem.begin(); it != GameObject::staticGameObjectsRem.end(); ++it)
	{
		auto remObj = std::find(gameObjects.begin(), gameObjects.end(), *it);

		// Add it to the appropriate lists
		if ((*remObj)->isUpdatable())
			model->remUpdatable(dynamic_cast<Updatable*>(*remObj));
		if ((*remObj)->isDrawable())
			view->remDrawable(dynamic_cast<Drawable*>(*remObj));
		if ((*remObj)->isCollidable())
			model->remCollidable(dynamic_cast<Collidable*>(*remObj));

		gameObjects.erase(remObj);
	}
	GameObject::staticGameObjectsRem.clear();

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
	This function creates and adds many GameObjects to the initial list for the game.
*/
void Controller::initObjects()
{
	p = new Player();
	addObject(p);

	Wall* w1 = new Wall(vec::Vector2(-64 * 1, -64 * 3),
		vec::Vector2(64 * 1, 64 * 3),
		new sf::Texture());
	addObject(w1);
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