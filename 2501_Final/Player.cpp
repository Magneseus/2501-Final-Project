#include "Player.h"
#include <iostream>

Player::Player()
{
	Rect* r = new Rect(
		vec::Vector2(-20, -20), 
		vec::Vector2(20, 0),
		vec::Vector2(40, 20),
		vec::Vector2(-40, 40));
	col.addShape(r);

	Circ* c = new Circ(vec::Vector2(50, 0), 20);
	col.addShape(c);

	setTag(sf::String("Player"));
}

Player::~Player()
{

}



void Player::update(const sf::Time& delta)
{
	setPosition(mCoords);

	vec::Vector2 newPosH(mCoords.x, mCoords.y);
	col.moveTo(newPosH);

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

	target.draw(col, states);
}

void Player::setMCoords(const sf::Vector2i& mouse)
{
	mCoords = sf::Vector2f(mouse.x, mouse.y);
}

void Player::rot(float x)
{
	col.rotate(x);
}