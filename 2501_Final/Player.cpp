#include "Player.h"

Player::Player()
{

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}



void Player::update(const sf::Time& delta)
{

}

void Player::onCollide(const Collidable& other)
{
	std::cout << "Collide!: " + other.getTag().toAnsiString();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	// Draw collision box
	target.draw(col, states);
}