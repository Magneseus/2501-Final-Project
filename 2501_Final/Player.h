#pragma once

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Vector.h"
#include "Vehicle.h"
#include "Projectile.h"
#include "Weapon.h"

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

class Player : public Entity
{
public:
	Player();
	~Player();

	sf::Texture playerTexture;
	sf::Sprite player;

	Vehicle* vehicle;
	sf::Clock vehicleEnterCooldown;
	sf::Time vehicleEnterTime;

	virtual void update(const sf::Time&);		// from Updatable
	virtual void onCollide(Collidable& other);	// from Collidable

	void enterVehicle(Vehicle* v);
	void exitVehicle();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable
	
	Weapon* primary;

	const float onFootAccel = 0;
	const float onFootTopSpeed = 100;
	const float onFootRotateSpeed = 180;
};