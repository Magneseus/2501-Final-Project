#pragma once

#include "Model.h"
#include "View.h"
#include "GameObject.h"
#include <SFML\Window.hpp>

class Controller
{
public:
	Controller(Model*, View*);
	~Controller();
	
	void input();

	const enum GSTATES{MENU, GAME, SIZE} GSTATE;
	
private:
	Model* model;
	View* view;
	
};