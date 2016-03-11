#include "Player.h"

Player::Player()
{
	vel = vec::Vector2(0,0);

	vehicle = new TransportShip();

	addObjectStatic(vehicle);

	vehicle = new BasicShip();
	vehicle->pos = vec::Vector2(200, 250);
	vehicle->vel = vec::Vector2(10, 10);

	addObjectStatic(vehicle);

	vehicle = NULL;

	vehicleEnterTime = sf::seconds(1);

	playerTexture.loadFromFile("img/player.png");
	player.setTexture(playerTexture);
	
	player.setOrigin(25, 25);

	pos = vec::Vector2(300, 300);

	bearing = 0;

	accelRate = onFootAccel;
	topSpeed = onFootTopSpeed;
	rotateSpeed = onFootRotateSpeed;

	// Add a collison box for player
	Rect* r = new Rect(vec::Vector2(-20, -20), vec::Vector2(20, 20));
	col.addShape(r);

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

//float Player::getRotationSpeed() { return (vehicle == NULL) ? 180 : vehicle->getRotationSpeed(); }
//float Player::getAcceleration() { return (vehicle == NULL) ? 0 : vehicle->getAcceleration(); }

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
		else {
			motion = FORWARD;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (vehicle == NULL) {
			vel.setY(100);
		}
		else {
			motion = REVERSE;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (vehicle == NULL) {
			vel.setX(100);
		}
		else {
			strafe = RIGHT;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (vehicle == NULL) {
			vel.setX(-100);
		}
		else {
			strafe = LEFT;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && 
			vehicleEnterCooldown.getElapsedTime() > vehicleEnterTime)
	{
		exitVehicle();
	}

	float temp = bearing;

	Entity::update(delta);
	
	float deltaBearing = temp - bearing;
	//if (deltaBearing) std::cout << "Bearing changed by " << deltaBearing << std::endl;

	player.setPosition(pos.getX(), pos.getY());
	col.moveTo(pos);
	//col.rotateTo(bearing);

	if (vehicle != NULL) {
		vehicle->pos = pos;
		vehicle->bearing = bearing;
		vehicle->update(delta);
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

void Player::enterVehicle(Vehicle* v) {
	if (v != NULL) {
		remObjectStatic(v);
	}
	else { return; }	// if it's not a vehicle, don't try to use it

	vehicle = v;

	bearing = v->ship.getRotation();
	pos.setX(v->getPosition().x);
	pos.setY(v->getPosition().y);

	accelRate = v->getAcceleration();
	topSpeed = v->getTopSpeed();
	rotateSpeed = v->getRotationSpeed();

	vehicleEnterCooldown.restart();
}

void Player::exitVehicle() {
	if (vel.getMag() < 50) {

		addObjectStatic(vehicle);

		vehicle = NULL;
		vel.setX(0);
		vel.setY(0);

		accelRate = onFootAccel;
		topSpeed = onFootTopSpeed;
		rotateSpeed = onFootRotateSpeed;

		vehicleEnterCooldown.restart();
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
			enterVehicle(dynamic_cast<Vehicle*>(&other));
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
	// target.draw(col, states);
}