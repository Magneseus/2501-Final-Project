#pragma once

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include <SFML\System\Clock.hpp>

class Game
{
public:
	Game();
	~Game();
	
	void loop();
	
private:
	Model* model;
	View* view;
	Controller* controller;

	sf::Clock clock;
};