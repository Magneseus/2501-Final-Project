#include "Controller.h"

Controller::Controller(Model* m, View* v)
	: model(m),
	view(v),
	GSTATE(GSTATES::GAME)
{
	//addObject(&p);
	//addObject(&p1);

	GameObject* player = new Player();

	p = dynamic_cast<Player*>(player);
	addObject(player);
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
//	p.setMCoords(sf::Mouse::getPosition(view->window));

	p->motion = p->STILL;
	p->turning = p->STILL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		p->motion = p->FORWARD;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		p->motion = p->REVERSE;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		p->turning = p->CLWISE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		p->turning = p->COCLWISE;
	}

	// Set the view's global transform
	sf::Transform playerPos;
	playerPos.translate(-p->pos);
	playerPos.translate(view->WINDOW_WIDTH / 2, view->WINDOW_HEIGHT / 2);

	view->setTransform(playerPos);
}

void Controller::gameController()
{
	// Check the static list for objects to add
	for (auto it = GameObject::staticGameObjects.begin(); it != GameObject::staticGameObjects.end(); ++it)
	{
		addObject(*it);
	}

	// Check the static list for objects to delete
	for (auto it = GameObject::staticGameObjectsDel.begin(); it != GameObject::staticGameObjectsDel.end(); ++it)
	{
		delObject(*it);
	}

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