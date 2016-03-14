#pragma once

#include "GameObject.h"
#include "Weapon.h"

class Turret : public Entity {
public:
	Turret(vec::Vector2 p, Weapon* w);
	~Turret();

	virtual void onCollide(Collidable& other);
	virtual void update(const sf::Time& delta);

private:
	sf::Sprite s;
	sf::Texture i;

	Weapon* main;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};