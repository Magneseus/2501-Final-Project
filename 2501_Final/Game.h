#pragma once

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include <sstream>

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

	void createMainMenu();
	void createCredits();
	void createGameOver();
	void createSpawnMenu();

	sf::Clock clock;
	sf::Clock renderClock;
	sf::Time timePerFrame;
	const float frameRate = 120.0f;
};