#pragma once

#include "GameObject.h"

class Mainframe : public Entity {
public:
	Mainframe();
	~Mainframe();

	virtual void update(const sf::Time&);
	virtual void onCollide(Collidable& other);

	sf::Sprite computer;
	sf::Texture compTexture;

	virtual void takeDamage(float amount, Entity* source);

private:
	virtual void onDeath(Entity* killer);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};