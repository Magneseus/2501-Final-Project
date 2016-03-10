
#include "Vehicle.h"

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ship, states);
	//target.draw(col, states);
}

void Vehicle::onCollide(Collidable& other) {

}

float Vehicle::getAcceleration()	{ return accel; }
float Vehicle::getRotationSpeed()	{ return rotateSpeed; }
float Vehicle::getTopSpeed()		{ return topSpeed; }

BasicShip::BasicShip() {
	accel = 250;
	rotateSpeed = 180;

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

void BasicShip::update(const sf::Time& delta) {
	col.moveTo(vec::Vector2(getPosition().x, getPosition().y));
}