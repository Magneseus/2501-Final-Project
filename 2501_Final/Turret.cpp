
#include "Turret.h"

Turret::Turret(vec::Vector2 p, Weapon* w, float min, float max) {
	position = p;
	main = w;

	minRotation = min;
	maxRotation = max;

	rotation = minRotation + std::rand() % maxRotation;

	i.loadFromFile("img/smallturret.png");
	s.setOrigin(16, 16);
	s.setPosition(position.getSfVec());
	s.setTexture(i);

	Rect* r = new Rect(vec::Vector2(-15, -15), vec::Vector2(25, 15));
	col.addShape(r);
	col.moveTo(position);

	state = IDLE;

	rotateSpeed = 360;
}

Turret::~Turret() {}

void Turret::update(const sf::Time& delta) {
	//Entity::update(delta);

	if (state == IDLE) {
		rotateSpeed = idleRotateSpeed;
	} else if (state == ACTIVE) {
		rotateSpeed = activeRotateSpeed;
	}

	if (rotation > maxRotation) {
		sign = -1;
	}
	else if (rotation < minRotation) {
		sign = 1;
	}

	/*if (frenzyTimer.getElapsedTime().asSeconds() > 1) {
		if (std::rand() % 100 > 50) sign = (sign == -1) ? 1 : -1;
		frenzyTimer.restart();
	}*/

	rotation += delta.asSeconds() * rotateSpeed * sign;

	s.setRotation(rotation);
	col.rotateTo(toRadians(rotation));

	main->shoot(toRadians(rotation), position);
}

void Turret::onCollide(Collidable& other) {
	state = ACTIVE;
}

void Turret::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(s, states);
	target.draw(col, states);
}