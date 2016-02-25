#pragma once

#include "GameObject.h"
#include "SpriteSheet.h"

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Player : public Entity
{
public:
	Player();
	~Player();

	virtual void update(const sf::Time&);
	virtual void onCollide(const Collidable& other);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};