
#include "Turret.h"

Turret::Turret(vec::Vector2 p, Weapon* w) {
	pos = p;
	main = w;

	i.loadFromFile("img/smallturret.png");
	s.setOrigin(16, 16);
	s.setPosition(pos.getSfVec());
	s.setTexture(i);

	rotateSpeed = 90;
}

Turret::~Turret() {}

void Turret::update(const sf::Time& delta) {
	//Entity::update(delta);
	
	bearing += delta.asSeconds() * rotateSpeed;

	s.setRotation(bearing);

	main->shoot(toRadians(bearing), pos);
}

void Turret::onCollide(Collidable& other) {}

void Turret::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(s, states);
}