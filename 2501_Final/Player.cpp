#include "Player.h"

Player::Player()
{
	shipStill.loadFromFile("img/medspeedster.png");
	shipThrusting.loadFromFile("img/shipthrusting.png");

	shipTexture = shipStill;

	ship.setTexture(shipTexture);

	ship.setOrigin(30, 42.5);

	pos = vec::Vector2(300, 100);

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
		//turning = CLWISE;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//turning = COCLWISE;
	}

	float speed = 250;
	float rotateSpeed = 180.f;	// 180° per second

	// Get the vector between the mouse and the player
	vec::Vector2 mousePos = vec::Vector2(Global::mouseWindowCoords.x, Global::mouseWindowCoords.y);
	vec::Vector2 mDif = mousePos - vec::Vector2(400, 400);

	// Get the current turning direction
	vec::Vector2 turnVec(toRadians(bearing));

	// Set the turning direction
	double angDif = toDegrees(mDif.angleBetween(turnVec));
	angDif *= mDif.cross(turnVec) < 0 ? -1 : 1;

	if (angDif < 1 && angDif > -1)
		turning = STILL;
	else if (angDif < -1)
		turning = CLWISE;
	else
		turning = COCLWISE;

	bearing += delta.asSeconds() * rotateSpeed * turning;

	// Bind bearing
	if (bearing > 360)
		bearing = std::fmod(bearing, 360.0f);
	else if (bearing < 0)
		bearing = 360.0f - std::fmod(std::abs(bearing), 360.0f);

	// Calculate acceleration
	vec::Vector2 accel(toRadians(bearing));
	accel.setMag(speed * motion * delta.asSeconds());
	vel += accel;

	// Calculate position
	pos += vel * delta.asSeconds();

	ship.setPosition(pos.getX(), pos.getY());

	// Set the textures
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
	states.transform.rotate(bearing, pos.getX(), pos.getY());

	target.draw(ship, states);

	// Draw collision box
	//target.draw(col, states);
}