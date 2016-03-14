#pragma once

#include "GameObject.h"
#include "Weapon.h"

class Turret : public Entity {
public:
	Turret(vec::Vector2 p, Weapon* w, float min, float max);
	~Turret();

	virtual void onCollide(Collidable& other);
	virtual void update(const sf::Time& delta);

private:
	sf::Sprite s;
	sf::Texture i;

	enum STATES {IDLE, ACTIVE};
	int state;
	const float idleRotateSpeed = 45;
	const float activeRotateSpeed = 90;

	sf::Clock frenzyTimer;

	int maxRotation, minRotation;	// in degrees
	int sign = 1;	// 1 clockwise, -1 counterclockwise

	Weapon* main;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};