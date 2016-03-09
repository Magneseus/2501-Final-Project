#pragma once

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Vector.h"

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

class Player : public Entity
{
public:
	Player();
	~Player();

	sf::Vector2f pos;	// the in world coords of player, player is always drawn at w/2, h/2
	sf::Vector2f vel;
	sf::Vector2f accel; 
	float bearing;		// in degrees

	enum {FORWARD = 1, REVERSE = -1, STILL = 0, CLWISE = 1, COCLWISE = -1};
	int motion, turning;

	sf::Texture shipTexture;
	sf::Texture shipThrusting;
	sf::Texture shipStill;
	sf::Sprite ship;

	virtual void update(const sf::Time&);										// from Updatable
	virtual void onCollide(const Collidable& other);							// from Collidable

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable

};