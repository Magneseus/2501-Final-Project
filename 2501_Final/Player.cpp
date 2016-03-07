#include "Player.h"
#include <iostream>

Player::Player()
{
	Rect* r = new Rect(
		vec::Vector2(-20, -20), 
		vec::Vector2(20, 0),
		vec::Vector2(40, 20),
		vec::Vector2(-40, 40));

	r->rotate(2.0f);
	hitbox.push_back(r);

	setTag(sf::String("Player"));
}

Player::~Player()
{

}



void Player::update(const sf::Time& delta)
{
	setPosition(mCoords);

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		vec::Vector2 newPosH(mCoords.x, mCoords.y);
		(*it)->setPos(newPosH);
	}

	time = delta;
}

void Player::onCollide(const Collidable& other)
{
	std::cout << "Collide!: " + other.getTag().toAnsiString() << " : T(" << time.asSeconds() << ")" << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	/*
	sf::RectangleShape rec;
	rec.setFillColor(sf::Color::Red);

	rec.setSize(sf::Vector2f(30, 30));
	rec.setOrigin(sf::Vector2f(15, 15));
	rec.setPosition(getPosition());
	  

	target.draw(rec, states);
	*/

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		target.draw(**it, states);
	}
}

void Player::setMCoords(const sf::Vector2f& mouse)
{
	mCoords = mouse;
}