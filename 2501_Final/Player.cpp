#include "Player.h"

Player::Player()
{
	vel = sf::Vector2f(0,0);

	shipStill.loadFromFile("img/medspeedster.png");
	shipThrusting.loadFromFile("img/shipthrusting.png");

	shipTexture = shipStill;

	ship.setTexture(shipTexture);

	ship.setOrigin(30, 42.5);

	pos = sf::Vector2f(300, 100);

	bearing = 0;

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

void Player::update(const sf::Time& delta) {

	motion = STILL;
	turning = STILL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		motion = FORWARD;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		motion = REVERSE;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		turning = CLWISE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		turning = COCLWISE;
	}

	float speed = 250;
	float rotateSpeed = 180.f;	// 180° per second

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
	states.transform.rotate(bearing, pos.x, pos.y);

	target.draw(ship, states);

	// Draw collision box
	//target.draw(col, states);
}