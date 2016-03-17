#pragma once

#include "GameObject.h"

class Projectile : public Entity {
public:
	Projectile(Entity* shooter, vec::Vector2 v, vec::Vector2 p, float dam, float speed);
    ~Projectile();

	int getDamage();

	virtual void update(const sf::Time&);
	virtual void onCollide(Collidable& other);

private:
	Entity* parent;
	float damage;
	sf::Sprite sprite;

	virtual void onDeath(Entity*);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};