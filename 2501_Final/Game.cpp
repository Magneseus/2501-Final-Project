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

		// check to ensure game state matches UI state

		if (Global::getState() != view->menu->getState()) {
			view->menu->setState(Global::getState());

			switch (Global::getState()) {
			case Global::S_SPAWNING:
				createSpawnMenu();
				break;
			case Global::S_WIN:
				createWinScreen();
				Global::GAMEOVER = true;
				break;
			case Global::S_PLAY:
				view->menu->clear();
				break;
			}
		}

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
		"Space Protectors", 42);

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y,
		150, 50,
		"Play",
		std::bind(&Controller::initObjects, controller));

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y * 1.25,
		150, 50,
		"Instructions",
		std::bind(&Game::createHelpMenu, this));

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y * 1.5,
		150, 50,
		"Credits",
		std::bind(&Game::createCredits, this));
}

void Game::createHelpMenu()
{
	UI* ui = view->menu;

	ui->clear();

	std::stringstream inst;

	inst << "Your goal is to destroy the evil enemy AI Mainframe." << std::endl;
	inst << "You can track it by following your compass when you get into a ship." << std::endl << std::endl;

	inst << "Press F to get in/out of a ship.\nUse WASD to move and the mouse to fire.\nUse Z to slow down in a ship.\nUse your right click to alt. fire.";

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		inst.str(),
		20);

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y*1.5,
		150, 50,
		"Main Menu",
		std::bind(&Game::createMainMenu, this));
}

void Game::createCredits() {
	UI* ui = view->menu;

	ui->clear();

	std::stringstream credits;

	credits << "Space Protectors made by Matt Mayer and Kyle Causton" << std::endl;
	credits << "Made for COMP2501 at Carleton University, 2016";

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		credits.str(),
		20);

	ui->addButton(Global::middleWindowCoords.x, Global::middleWindowCoords.y*1.5,
		150, 50,
		"Main Menu",
		std::bind(&Game::createMainMenu, this));
}

void Game::createGameOver() {
	UI* ui = view->menu;

	ui->clear();

	std::stringstream string;

	string << "You have died." << std::endl;
	string << "The." << std::endl;

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		string.str(),
		20);
}

void Game::createSpawnMenu() {
	UI* ui = view->menu;

	ui->clear();

	ui->addButton(Global::middleWindowCoords.x*1.5, Global::middleWindowCoords.y*0.5,
		100, 50,
		"Medium",
		std::bind(&Player::getLoadoutOne, controller->p));

	ui->addButton(Global::middleWindowCoords.x*1.5, Global::middleWindowCoords.y,
		100, 50,
		"Light",
		std::bind(&Player::getLoadoutTwo, controller->p));

	ui->addButton(Global::middleWindowCoords.x*1.5, Global::middleWindowCoords.y*1.5,
		100, 50,
		"Heavy",
		std::bind(&Player::getLoadoutThree, controller->p));
}

void Game::createWinScreen() {
	UI* ui = view->menu;

	ui->clear();

	std::stringstream end;

	end << "You did it!" << std::endl;
	end << "You stopped the AI from terrorizing the galaxy." << std::endl;
	end << "Return to base, you did well." << std::endl;

	ui->addTextBox(Global::middleWindowCoords.x, Global::middleWindowCoords.y*0.5,
		0, 0,
		end.str(), 30);

}