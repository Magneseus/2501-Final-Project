#include "Game.h"

Game::Game()
{
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);
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
		view->render();
	}
}