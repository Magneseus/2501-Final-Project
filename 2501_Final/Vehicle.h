#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "AnimatedSprite.h"

/*					Vehicle
	Entities visible on screen, can be interacted 
	with to get in (Trigger?). Basically a storage
	class - holds different accelerations and data
	on movement. Also stores the textures of the 
	ship.

	TODO: Privatize vehicle, make player friend class
*/	

class Vehicle : public Entity {
public:
	virtual ~Vehicle() {}

	// update is written by each ship
	void update(const sf::Time&);	// from Updatable

	virtual void onCollide(Collidable& other);	// from Collide

	float getAcceleration();
	float getTopSpeed();
	float getRotationSpeed();
	float getDragValue();

	AnimatedSprite* ship;

	Loadout* weapons;

protected:
	float baseAccel, baseTopSpeed, baseRotateSpeed;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable
};

class BasicShip : public Vehicle {
public:
	BasicShip();
	~BasicShip();

	//void update(const sf::Time&);
};

class TransportShip : public Vehicle {
public:
	TransportShip();
	~TransportShip();
};