#include "Game.h"

Game::Game()
{
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);

	timePerFrame = sf::seconds(1.0f / frameRate);

	createMainMenu();

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
		if(controller->p) controller->gameController();
		model->update(clock.restart());

		if (renderClock.getElapsedTime() > timePerFrame)
		{
			view->addFPS(renderClock.getElapsedTime());
			view->render();
			renderClock.restart();
		}
	}
}

void Game::createMainMenu() {
	UI* ui = view->menu;
	
	ui->clear();

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		"Space Game", 42);

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y,
		150, 50,
		"Play",
		std::bind(&Controller::initObjects, controller));

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y * 1.5,
		150, 50,
		"Credits",
		std::bind(&Game::createCredits, this));
}

void Game::createCredits() {
	UI* ui = view->menu;

	ui->clear();

	std::stringstream credits;

	credits << "Space Game made by Matt Mayer and Kyle Causton" << std::endl;
	credits << "Made for COMP2501 at Carleton University, 2016" << std::endl;

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		credits.str(),
		20);

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y*1.5,
		150, 50,
		"Main Menu",
		std::bind(&Game::createMainMenu, this));
}