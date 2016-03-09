#include "Player.h"

Player::Player()
{
	vel = sf::Vector2f(0,0);

	shipStill.loadFromFile("img/medspeedster.png");
	shipThrusting.loadFromFile("img/shipthrusting.png");

	shipTexture = shipStill;

	ship.setTexture(shipTexture);

	pos = sf::Vector2f(300, 100);

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

void Player::update(const sf::Time& delta) {
	/*float rotateSpeed = 90.f / 1000.f;

	playerBearing += deltaTime * rotateSpeed * turning;


	// find the components of the "forward" vector,
	//	forward being relative to the rotation

	float speed = 125.f / 1000.f;	// 100 pixels per second

	playerPos.x += cos(((playerBearing + 90) * M_PI) / 180) * motion * speed * deltaTime;
	playerPos.y += sin(((playerBearing + 90) * M_PI) / 180) * motion * speed * deltaTime;*/


	float speed = 0.0005 / 1000000;		// 125 pixels per second
	float rotateSpeed = 180.f / 1000000;	// 90° per second

	vel.x += speed * motion * cos(toRadians(bearing)) * delta.asMicroseconds();
	vel.y += speed * motion * sin(toRadians(bearing)) * delta.asMicroseconds();

	bearing += delta.asMicroseconds() * rotateSpeed * turning;

	pos.x += vel.x * delta.asMicroseconds() ;
	pos.y += vel.y * delta.asMicroseconds() ;

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

	states.transform.rotate(bearing, pos.x + 42.5, pos.y + 42.5);

	target.draw(ship, states);

	// Draw collision box
	//target.draw(col, states);
}