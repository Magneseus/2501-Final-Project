#pragma once

#include <functional>

#include "GameObject.h"
#include "Weapon.h"
#include "AnimatedSprite.h"

class Turret : public Entity {
	friend class Mainframe;

public:
	Turret(vec::Vector2 p, Weapon* w, float min, float max);
	Turret(vec::Vector2 p, Weapon* w, float min, float max, std::function<void()> callback);
	~Turret();

	virtual void onCollide(Collidable& other);
	virtual void update(const sf::Time& delta);	

private:
	AnimatedSprite* s;

	void changeState(int newState);

	enum STATES {IDLE, ACTIVE, FRENZIED};
	int state;
	const float idleRotateSpeed = 45;
	const float activeRotateSpeed = 90;

	sf::Clock frenzyTimer;

	virtual void takeDamage(float amount);
	virtual void onDeath();

	std::function<void()> deathCallback;	// used for spawned turrets

	int maxRotation, minRotation;	// in degrees
	int sign = 1;	// 1 clockwise, -1 counterclockwise

	Weapon* main;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};