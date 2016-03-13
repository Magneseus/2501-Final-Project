
#include "Weapon.h"

Weapon::Weapon(float fr, float dam, float inSpeed) {
	fireRate = fr;
	damage = dam;
	speed = inSpeed;
}

Weapon::~Weapon() {}

// takes angle as radians
void Weapon::shoot(float angle, vec::Vector2 origin) {
	if (cooldown.getElapsedTime().asSeconds() > 1/fireRate) {
		vec::Vector2 targ(angle);
		
		GameObject* p = new Projectile(origin, targ, damage, speed);
		GameObject::addObjectStatic(p);
		cooldown.restart();
	}
}