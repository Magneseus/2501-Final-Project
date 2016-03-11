
#include "Vehicle.h"

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ship, states);
	target.draw(col, states);
}

void Vehicle::onCollide(Collidable& other) {

}

float Vehicle::getAcceleration()	{ return baseAccel; }
float Vehicle::getRotationSpeed()	{ return baseRotateSpeed; }
float Vehicle::getTopSpeed()		{ return baseTopSpeed; }

void Vehicle::update(const sf::Time& delta) {
	ship.setPosition(pos.getX(), pos.getY());
	setPosition(pos.getX(), pos.getY());
	ship.setRotation(bearing);

	col.moveTo(vec::Vector2(getPosition().x, getPosition().y));
	col.rotateTo(toRadians(bearing));
}

BasicShip::BasicShip() {
	baseAccel = 250;
	baseRotateSpeed = 180;
	baseTopSpeed = 1000;

	shipTexture.loadFromFile("img/medspeedster.png");

	ship.setTexture(shipTexture);
	ship.setOrigin(30, 42.5);

	// Set collision box
	Rect* r = new Rect(vec::Vector2(-30, -50), vec::Vector2(50, 50));
	col.addShape(r);

	setTag(sf::String("Vehicle"));
}

BasicShip::~BasicShip() {

}

TransportShip::TransportShip() {
	baseAccel = 150;
	baseRotateSpeed = 90;
	baseTopSpeed = 500;

	shipTexture.loadFromFile("img/ship_transport.png");

	ship.setTexture(shipTexture);
	ship.setOrigin(42.5, 42.5);


	Rect* r = new Rect(vec::Vector2(-30, -50), vec::Vector2(50, 50));
	col.addShape(r);

	setTag(sf::String("Vehicle"));
}

TransportShip::~TransportShip() {}


//void BasicShip::update(const sf::Time& delta) {

//}

