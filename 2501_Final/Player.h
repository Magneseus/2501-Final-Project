#pragma once

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Vector.h"
#include "Vehicle.h"

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

class Player : public Entity
{
public:
	Player();
	~Player();

	vec::Vector2 pos;	// the in world coords of player, player is always drawn at w/2, h/2
	vec::Vector2 vel;
	vec::Vector2 accel;
	float bearing;		// in degrees

	enum DIRECTION {FORWARD = 1, REVERSE = -1, STILL = 0, CLWISE = 1, COCLWISE = -1};

	int motion, turning;

	sf::Texture playerTexture;
	sf::Sprite player;
	Vehicle* vehicle;

	virtual void update(const sf::Time&);										// from Updatable
	virtual void onCollide(const Collidable& other);							// from Collidable

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable

	float getRotationSpeed();
	float getAcceleration();

};