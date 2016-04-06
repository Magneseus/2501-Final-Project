#pragma once

#include "GameObject.h"

class Projectile : public Entity {
public:
	Projectile(std::vector<sf::String> tags, vec::Vector2 v, vec::Vector2 p, float dam, float speed);
    ~Projectile();

	int getDamage();

	virtual void update(const sf::Time&);
	virtual void onCollide(Collidable& other);

private:

	float damage;
	sf::Sprite sprite;

	sf::Clock lifeTime;

	virtual void onDeath();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};