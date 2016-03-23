
#include "Vehicle.h"

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*ship, states);

	drawHealthBar(target, states);
}

void Vehicle::onCollide(Collidable& other) {
}

float Vehicle::getAcceleration()	{ return baseAccel; }
float Vehicle::getRotationSpeed()	{ return baseRotateSpeed; }
float Vehicle::getTopSpeed()		{ return baseTopSpeed; }
float Vehicle::getDragValue()		{ return dragValue; }

void Vehicle::update(const sf::Time& delta) {
	ship->update(delta);
	ship->setPosition(position);
	setPosition(position);
	ship->setRotation(rotation);
	setRotation(rotation);
}

void Vehicle::onDeath(Entity* killer) {
	delObjectStatic(this);
}

BasicShip::BasicShip() {
	baseAccel = 250;
	baseRotateSpeed = 180;
	baseTopSpeed = 1000;
	dragValue = 0.15;

	weapons = new Loadout();
	weapons->primary = new Weapon(5, 10, 500);
	weapons->secondary = new Weapon(1, 50, 250);

	ship = new AnimatedSprite(Global::globalSpriteSheet, 10);

	std::vector<sf::String> names;
	names.push_back("basic_ship.png");
	ship->addState(names);

	names.clear();
	names.push_back("basic_thrust.png");
	ship->addState(names);

	ship->setPosition(position);
	ship->setRotation(rotation);

	//ship.setTexture(shipTexture);
	//ship.setOrigin(30, 42.5);

	// Set collision box
	Rect* r = new Rect(
		vec::Vector2(5, -40), 
		vec::Vector2(-25, 0),
		vec::Vector2(5, 40),
		vec::Vector2(50, 0));
	col.addShape(r);

	setTag(sf::String("Vehicle"));
}

BasicShip::~BasicShip() {}

TransportShip::TransportShip() {
	baseAccel = 150;
	baseRotateSpeed = 90;
	baseTopSpeed = 500;
	dragValue = 0.15;

	weapons = new Loadout();
	weapons->primary = new Weapon(1, 10, 500);
	weapons->secondary = new Weapon(0.5, 50, 1000);

	ship = new AnimatedSprite(Global::globalSpriteSheet , 10);

	std::vector<sf::String> names;
	names.push_back("transport_ship.png");
	ship->addState(names);
	names.clear();

	names.push_back("transport_thrust.png");
	ship->addState(names);
	names.clear();

	ship->setPosition(position);
	ship->setRotation(rotation);
	//ship.setOrigin(42.5, 42.5);

	Rect* r = new Rect(
		vec::Vector2(-30, -20),
		vec::Vector2(30, -10),
		vec::Vector2(30, 10),
		vec::Vector2(-30, 20));
	col.addShape(r);

	setTag(sf::String("Vehicle"));
}

TransportShip::~TransportShip() {}

