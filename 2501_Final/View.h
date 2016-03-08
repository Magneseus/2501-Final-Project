#pragma once

#include "Model.h"
#include "GameObject.h"
#include "SpriteSheet.h"

#include "AnimatedSprite.h"

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

class View
{
public:
	View(Model*);
	~View();
	
	void render();
	void addDrawable(Drawable*);
	bool delDrawable(Drawable*);

	int WINDOW_WIDTH, WINDOW_HEIGHT;
	sf::RenderWindow window;

	sf::Texture *a, *b, *c, *d;
	AnimatedSprite* temp;
	
private:
	Model* model;

	std::vector<Drawable*> drawables;
};