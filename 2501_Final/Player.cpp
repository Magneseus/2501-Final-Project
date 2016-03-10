#include "Player.h"

Player::Player()
{
	vel = vec::Vector2(0,0);

	vehicle = new BasicShip();
	vehicleEnterTime = sf::seconds(1);

	playerTexture.loadFromFile("img/player.png");
	player.setTexture(playerTexture);
	
	player.setOrigin(25, 25);

	pos = vec::Vector2(300, 100);

	bearing = 0;


	// Add a collison box for player
	Rect* r = new Rect(vec::Vector2(-20, -20), vec::Vector2(20, 20));
	col.addShape(r);

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
	strafe = STILL;

	if (vehicle == NULL) {
		vel.setX(0);
		vel.setY(0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (vehicle == NULL) {
			vel.setY(-100);
		}
		motion = FORWARD;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (vehicle == NULL) {
			vel.setY(100);
		}
		motion = REVERSE;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (vehicle == NULL) {
			vel.setX(100);
		}
		strafe = RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (vehicle == NULL) {
			vel.setX(-100);
		}
		strafe = LEFT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && 
			vehicleEnterCooldown.getElapsedTime() > vehicleEnterTime)
	{
		addObjectStatic(vehicle);

		vehicle = NULL;
		vel.setX(0);
		vel.setY(0);

		vehicleEnterCooldown.restart();
	}

	float speed = getAcceleration();
	float rotateSpeed = getRotationSpeed();

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

	vec::Vector2 strafeAccel(toRadians(bearing+90));
	strafeAccel.setMag(rotateSpeed * strafe * delta.asSeconds());
	vel += strafeAccel;

	// Calculate position
	pos += vel * delta.asSeconds();

	player.setPosition(pos.getX(), pos.getY());
	col.moveTo(pos);
	//col.rotateTo(bearing);

	if (vehicle != NULL)
	{
		vehicle->ship.setPosition(pos.getX(), pos.getY());
		vehicle->setPosition(pos.getX(), pos.getY());
		vehicle->ship.setRotation(bearing);
	}

	player.setRotation(bearing);

	// Set the textures
	if (motion == FORWARD) {
		//shipTexture = shipThrusting;
	}
	else {
		//shipTexture = shipStill;
	}
}

void Player::onCollide(Collidable& other)
{
	std::cout << "COLLIDE!: " << other.getTag().toAnsiString() << std::endl;
	if (other.getTag() == "Vehicle" && 
			vehicle == NULL && 
			vehicleEnterCooldown.getElapsedTime() > vehicleEnterTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			vehicle = dynamic_cast<Vehicle*>(&other);

			if (vehicle != NULL)
				remObjectStatic(vehicle);

			bearing = vehicle->ship.getRotation();
			pos.setX(vehicle->getPosition().x);
			pos.setY(vehicle->getPosition().y);

			vehicleEnterCooldown.restart();
		}
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform.rotate(bearing, pos.getX(), pos.getY());

	if (vehicle != NULL) {
		target.draw(*vehicle, states);
	} else {
		target.draw(player, states);
	}
	// Draw collision box
	target.draw(col, states);
}