
#include "Projectile.h"

Projectile::Projectile(vec::Vector2 p, vec::Vector2 v, float dam, float speed) {
	vel = v;
	position = p;
	damage = dam;
	topSpeed = speed;

	accelRate = 0;
	rotateSpeed = 0;

	Circ* c = new Circ(vec::Vector2(0, 0), 5);
	col.addShape(c);

	setTag(sf::String("Projectile"));
}

Projectile::~Projectile() {}

int Projectile::getDamage() { return damage; }

void Projectile::update(const sf::Time& delta) {
	vel.setMag(topSpeed);

	Entity::update(delta);
}

void Projectile::onCollide(Collidable& other) { 
	//if(other.getTag() != "Player" && other.getTag() != "Projectile")
	//	delObjectStatic(this); 
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape s(5);
	s.setPosition(position.getSfVec());
	s.setFillColor(sf::Color::Yellow);
	s.setOrigin(5, 5);

	target.draw(s, states);
}