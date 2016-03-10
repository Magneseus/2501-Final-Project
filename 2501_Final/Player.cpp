#include "Player.h"

Player::Player()
{
	vel = sf::Vector2f(0,0);

	vehicle = new BasicShip();

	playerTexture.loadFromFile("img/player.png");
	player.setTexture(playerTexture);
	
	player.setOrigin(25, 25);

	pos = sf::Vector2f(300, 100);

	bearing = 0;

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

float Player::getRotationSpeed() { return (vehicle == NULL) ? 180 : vehicle->getRotationSpeed(); }
float Player::getAcceleration() { return (vehicle == NULL) ? 0 : vehicle->getAcceleration(); }

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) vehicle = NULL;

	float accel = getAcceleration();
	float rotateSpeed = getRotationSpeed();

	bearing += delta.asSeconds() * rotateSpeed * turning;

	vel.x += accel * motion * cos(toRadians(bearing)) * delta.asSeconds();
	vel.y += accel * motion * sin(toRadians(bearing)) * delta.asSeconds();

	pos.x += vel.x * delta.asSeconds();
	pos.y += vel.y * delta.asSeconds();

	player.setPosition(pos.x, pos.y);

	if (vehicle != NULL) vehicle->ship.setPosition(pos.x, pos.y);

	if (motion == FORWARD) {
	//	shipTexture = shipThrusting;
	}
	else {
		//shipTexture = shipStill;
	}
}

void Player::onCollide(const Collidable& other)
{
	std::cout << "Collide!: " + other.getTag().toAnsiString();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.rotate(bearing, pos.x, pos.y);

	if (vehicle != NULL) {
		target.draw(*vehicle, states);
	} else {
		target.draw(player, states);
	}
	// Draw collision box
	//target.draw(col, states);
}