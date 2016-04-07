
#pragma once

#include "Projectile.h"
#include "GameObject.h"

class Weapon {
public:
	Weapon(sf::String inName, float fr, float dam, float inSpeed);
	~Weapon();

	sf::String getName();

	void shoot(float angle, vec::Vector2 origin, std::vector<sf::String> allies);

private:
	float fireRate, damage, speed;
	sf::String name;

	sf::Clock cooldown;
};

struct Loadout {
	Weapon* primary;
	Weapon* secondary;
};
