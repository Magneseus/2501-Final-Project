#pragma once

#include "Projectile.h"
#include "GameObject.h"

class Weapon {
public:
	Weapon(float fr, float dam, float inSpeed);
	~Weapon();

	void shoot(float angle, vec::Vector2 origin);

private:
	float fireRate, damage, speed;

	sf::Clock cooldown;
};

struct Loadout {
	Weapon* primary;
	Weapon* secondary;
};
