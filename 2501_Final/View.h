#pragma once

#include "Model.h"
#include "GameObject.h"
#include "SpriteSheet.h"
#include "UI.h"
#include "Player.h"

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <queue>

class View
{
public:
	View(Model*);
	~View();
	
	void render();
	void addDrawable(Drawable*, bool addBack=false);
	bool delDrawable(Drawable*);
	bool remDrawable(Drawable*);
	
	void setTransform(const sf::Transform&);
	sf::Transform getTransform();

	void addFPS(const sf::Time&);

	int WINDOW_WIDTH, WINDOW_HEIGHT;
	sf::RenderWindow window;

	UI* menu;

	sf::Sprite HUD;
	sf::Texture HUDTexture;

	sf::Sprite compassNeedle;
	sf::Sprite compassBase;
	sf::Texture compassNeedleTex;
	sf::Texture compassBaseTex;

	sf::Text equippedWeapon;
	sf::Text holsteredWeapon;

	void drawHUD();

	//sf::Texture *a, *b, *c, *d;
	//AnimatedSprite* temp;

	void spawnRenderables();
	
	sf::Texture hangar_tile;
	sf::Sprite hangar, enemyHangar;

	sf::Texture backgroundTex;
	sf::Sprite background;

private:
	Model* model;
	std::vector<Drawable*> drawables;
	sf::Transform globalTransform;

	std::deque<float> fps;
	sf::Text fpsText, mCoordsText;
	bool showFPS;
	bool renderablesSpawned;
};