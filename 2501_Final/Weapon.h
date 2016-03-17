
#pragma once

#include "Projectile.h"
#include "GameObject.h"

class Entity;

class Weapon {
public:
	Weapon(float fr, float dam, float inSpeed);
	~Weapon();

	void shoot(float angle, vec::Vector2 origin, Entity* parent);

private:
	float fireRate, damage, speed;

	sf::Clock cooldown;
};

struct Loadout {
	Weapon* primary;
	Weapon* secondary;
};
