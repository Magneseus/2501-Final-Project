#pragma once

#include "Model.h"
#include "View.h"
#include "GameObject.h"
#include "Player.h"
#include "StaticSolids.h"
#include "UI.h"
#include "Trigger.h"
#include "Mainframe.h"

#include <SFML\Window.hpp>

#include <vector>

class Controller
{
public:
	friend class Game;

	Controller(Model*, View*);
	~Controller();
	
	void input();
	void gameController();

	const enum GSTATES{MENU, GAME, SIZE} GSTATE;

private:
	void addObject(GameObject*);
	bool delObject(GameObject*);

	void initObjects();
	//TMP
	void enemyHangar();

	Model* model;
	View* view;

	std::vector<GameObject*> gameObjects;

	Player* p;
};