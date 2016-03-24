#include "Controller.h"

Controller::Controller(Model* m, View* v)
	: model(m),
	view(v),
	GSTATE(GSTATES::GAME)
{
	// Load the master spritesheet
	Global::globalSpriteSheet = new SpriteSheet(sf::String("img/masterSheet.png"));

}

Controller::~Controller()
{
	
}

void Controller::input()
{
	// reset player's important key presses
	if (p) {
		p->inputs.F = false;
		p->inputs.RClick = false;
	}
		// EVENT-BASED INPUT
	sf::Event e;
	while (view->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			view->window.close();
			break;

		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::Escape)
				view->window.close();
			break;

		case sf::Event::KeyPressed:
			if (p && e.key.code == sf::Keyboard::F) p->inputs.F = true;
			break;

		case sf::Event::Resized:
			view->WINDOW_WIDTH = e.size.width;
			view->WINDOW_HEIGHT = e.size.height;
			Global::middleWindowCoords = sf::Vector2i(e.size.width / 2, e.size.height / 2);
			break;

		case sf::Event::MouseButtonPressed:
			if (view->menu->processClick(e.mouseButton.x, e.mouseButton.y)) break;
			if (p && e.mouseButton.button == sf::Mouse::Right) p->inputs.RClick = true;
			break;
		}

		if (!view->window.isOpen())
			break;
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

	// Set the global DEBUG state
	Debug::debugging = Global::DEBUG;

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
	// Player
	p = new Player();
	addObject(p);

	Global::player = p;

	// Hangar shield
	sf::Texture* shieldTex = Global::globalSpriteSheet->getTex("shield_64.png");
	shieldTex->setRepeated(true);

	PlayerShield* w4 = new PlayerShield(vec::Vector2(-32, -64 * 5),
		vec::Vector2(32, 64 * 5),
		shieldTex);
	w4->setPosition(vec::Vector2(64 * 5, 0));
	addObject(w4);
	
	// Hangar Walls
	sf::Texture* wallTex = Global::globalSpriteSheet->getTex(sf::String("wall_64.png"));
	wallTex->setRepeated(true);

	Wall* w1 = new Wall(vec::Vector2(-32, -64 * 5),
		vec::Vector2(32, 64 * 5),
		wallTex);
	w1->setPosition(vec::Vector2(-64*5, 0));
	addObject(w1);

	Wall* w2 = new Wall(vec::Vector2(-32.f, -64 * 5.5f),
		vec::Vector2(32.f, 64 * 5.5f),
		wallTex);
	w2->setPosition(vec::Vector2(0, -64 * 5));
	w2->setRotation(90);
	addObject(w2);

	Wall* w3 = new Wall(vec::Vector2(-32.f, -64 * 5.5f),
		vec::Vector2(32.f, 64 * 5.5f),
		wallTex);
	w3->setPosition(vec::Vector2(0, 64 * 5));
	w3->setRotation(90);
	addObject(w3);

	// Hangar shield
	PlayerShield* w4 = new PlayerShield(vec::Vector2(-32, -64 * 5),
		vec::Vector2(32, 64 * 5),
		wallTex);
	w4->setPosition(vec::Vector2(64 * 5, 0));
	addObject(w4);
	
	// Hangar roof

	// Vehicles
	Vehicle* vehicle = new TransportShip();
	vehicle->setPosition(vec::Vector2(200, -200));
	vehicle->vel = vec::Vector2(10, 10);
	addObject(vehicle);

	vehicle = new BasicShip();
	vehicle->setPosition(vec::Vector2(200, 200));
	vehicle->vel = vec::Vector2(10, 10);

	addObject(vehicle);
	vehicle = NULL;

	// Enemies
	Turret* turret = new Turret(vec::Vector2(500, 100), new Weapon(3, 50, 250), 90, 180);
	addObject(turret);

	// General visual stuff
	view->spawnRenderables();

	// UI
	view->menu->clear();
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