#include "Game.h"

Game::Game()
{
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);

	timePerFrame = sf::seconds(1.0f / frameRate);
}

Game::~Game()
{
	delete controller;
	delete view;
	delete model;
}

void Game::loop()
{
	while (view->window.isOpen())
	{
		controller->input();
		model->update(clock.restart());

		if (renderClock.getElapsedTime() > timePerFrame)
		{
			view->render();
			renderClock.restart();
		}
	}
}