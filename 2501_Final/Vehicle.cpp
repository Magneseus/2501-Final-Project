
#include "Vehicle.h"

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(ship, states);
}

void Vehicle::onCollide(const Collidable& other) {

}

float Vehicle::getAcceleration() { return accel; }
float Vehicle::getRotationSpeed() { return rotateSpeed; }
float Vehicle::getTopSpeed() { return topSpeed; }

void Vehicle::enter(Player* pass) {
	passenger = pass;
}

BasicShip::BasicShip() {
	accel = 250;
	rotateSpeed = 180;

	shipTexture.loadFromFile("img/medspeedster.png");

	ship.setTexture(shipTexture);
	ship.setOrigin(30, 42.5);
}

BasicShip::~BasicShip() {

}

void BasicShip::update(const sf::Time&) {

}