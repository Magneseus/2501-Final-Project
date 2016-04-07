
#include "Weapon.h"

Weapon::Weapon(sf::String inName, float fr, float dam, float inSpeed) {
	fireRate = fr;
	damage = dam;
	speed = inSpeed;
	name = inName;
}

Weapon::~Weapon() {}

sf::String Weapon::getName() { return name; }

// takes angle as radians
void Weapon::shoot(float angle, vec::Vector2 origin, std::vector<sf::String> allies) {
	if (fireRate && cooldown.getElapsedTime().asSeconds() > 1/fireRate) {
		vec::Vector2 targ(angle);
		
		GameObject* p = new Projectile(allies, origin, targ, damage, speed);
		GameObject::addObjectStatic(p);
		cooldown.restart();
	}
}