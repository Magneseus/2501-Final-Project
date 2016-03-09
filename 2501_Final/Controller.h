#pragma once

#include "Model.h"
#include "View.h"
#include "GameObject.h"
#include "Player.h"

#include <SFML\Window.hpp>

#include <vector>

class Controller
{
public:
	Controller(Model*, View*);
	~Controller();
	
	void input();
	void gameController();

	const enum GSTATES{MENU, GAME, SIZE} GSTATE;
	
private:
	void addObject(GameObject*);
	bool delObject(GameObject*);

	Model* model;
	View* view;

	std::vector<GameObject*> gameObjects;

	Player p, p1;
	
};