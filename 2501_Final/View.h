#pragma once

#include "Model.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "UI.h"

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <queue>

class View
{
public:
	View(Model*);
	~View();
	
	void render();
	void addDrawable(Drawable*);
	bool delDrawable(Drawable*);
	bool remDrawable(Drawable*);
	
	void setTransform(const sf::Transform&);
	sf::Transform getTransform();

	void addFPS(const sf::Time&);

	int WINDOW_WIDTH, WINDOW_HEIGHT;
	sf::RenderWindow window;

	UI* menu;

	//sf::Texture *a, *b, *c, *d;
	//AnimatedSprite* temp;

	void spawnRenderables();
	
	sf::Texture hangar_tile;
	sf::Sprite hangar;

	sf::Texture backgroundTex;
	sf::Sprite background;

private:
	Model* model;
	std::vector<Drawable*> drawables;
	sf::Transform globalTransform;

	std::deque<float> fps;
	sf::Text fpsText;
	bool showFPS;
	bool renderablesSpawned;
};