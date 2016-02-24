#include "Player.h"
#include <iostream>

Player::Player()
{
	std::cout << GameObject::gameObjectType;
}

Player::~Player()
{

}



void Player::update(const sf::Time&)
{

}

void Player::onCollide(const Collidable& other)
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}