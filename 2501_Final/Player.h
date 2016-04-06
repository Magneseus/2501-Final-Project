#pragma once

#include "GameObject.h"
#include "SpriteSheet.h"
#include "Vector.h"
#include "Vehicle.h"
#include "Projectile.h"
#include "Weapon.h"
#include "Turret.h"

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

struct InputStorage {
	bool F;
	bool RClick;
	bool LClick;
};

class Player : public Entity
{
public:
	Player();
	~Player();

	sf::Texture* playerTexture;
	sf::Sprite player;

	Vehicle* vehicle;

	InputStorage inputs;

	virtual void update(const sf::Time&);		// from Updatable
	virtual void onCollide(Collidable& other);	// from Collidable

	void enterVehicle(Vehicle* v);
	void exitVehicle();
	void spawn();

	void getLoadoutOne();
	void getLoadoutTwo();
	void getLoadoutThree();

private:
	Loadout* currentLoadout;	// player's current loadout (from vehicle)
	Weapon* currentWeapon;

	Loadout* onFootLoadout;		// player's loadout
	Collider onFootCollider;   // Player's collision box for on foot

	const float onFootAccel = 0;
	const float onFootTopSpeed = 100;
	const float onFootRotateSpeed = 180;

	virtual void onDeath();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable
	void switchLoadouts(Loadout* newest);
	void switchWeapons();
};