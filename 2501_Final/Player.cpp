#include "Player.h"

Player::Player()
{
	vel = sf::Vector2f(0,0);

	shipStill.loadFromFile("img/medspeedster.png");
	shipThrusting.loadFromFile("img/shipthrusting.png");

	shipTexture = shipStill;

	ship.setTexture(shipTexture);

	pos = sf::Vector2f(300, 100);

	bearing = 0;

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

void Player::update(const sf::Time& delta) {
	float speed = 250;
	float rotateSpeed = 180.f;	// 180° per second

	//std::cout << delta.asSeconds() << " " << delta.asMilliseconds() << " " << delta.asMicroseconds() << std::endl;

	bearing += delta.asSeconds() * rotateSpeed * turning;

	vel.x += speed * motion * cos(toRadians(bearing)) * delta.asSeconds();
	vel.y += speed * motion * sin(toRadians(bearing)) * delta.asSeconds();

	pos.x += vel.x * delta.asSeconds();
	pos.y += vel.y * delta.asSeconds();

	ship.setPosition(pos.x, pos.y);

	if (motion == FORWARD) {
		shipTexture = shipThrusting;
	}
	else {
		shipTexture = shipStill;
	}
}

void Player::onCollide(const Collidable& other)
{
	std::cout << "Collide!: " + other.getTag().toAnsiString();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.rotate(bearing, pos.x + 30, pos.y + 42.5);

	target.draw(ship, states);

	// Draw collision box
	//target.draw(col, states);
}