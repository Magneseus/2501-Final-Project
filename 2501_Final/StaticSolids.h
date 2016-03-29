#pragma once

/*
	This file holds several shapes that will act as walls, or
	barriers for our game.
*/

#include "GameObject.h"
#include <fstream>

class Wall : public Collidable, public Drawable
{
public:
	Wall(vec::Vector2 _topleft, vec::Vector2 _bottomright, sf::Texture* _tex);
	~Wall();

	virtual void onCollide(Collidable& other);
	void setPosition(vec::Vector2 newPos);
	void setRotation(double _rotation);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite wallSprite;
};

class PlayerShield : public Wall
{
public:
	PlayerShield(vec::Vector2 _topleft, vec::Vector2 _bottomright, sf::Texture* _tex);
	~PlayerShield();

	virtual void onCollide(Collidable& other);
};

std::vector<Wall*> loadWalls(sf::String& fileName, sf::Texture* wallTex);