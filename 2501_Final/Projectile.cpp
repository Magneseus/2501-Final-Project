
#include "Projectile.h"

Projectile::Projectile(Entity* shooter, vec::Vector2 p, vec::Vector2 v, float dam, float speed) {
	parent = shooter;

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

	if (lifeTime.getElapsedTime().asSeconds() >= 5) {
		std::cout << "A projectile has expired." << std::endl;
		onDeath(NULL);
	}
}

void Projectile::onDeath(Entity* killer) { delObjectStatic(this); }

void Projectile::onCollide(Collidable& other) {
	if (other.getTag() == "Projectile") return;

	Entity* temp = dynamic_cast<Entity*>(&other);

	if (temp != parent) {
		if (temp) temp->takeDamage(damage, parent);
		onDeath(temp);
	}
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape s(5);
	s.setPosition(position.getSfVec());
	s.setFillColor(sf::Color::Yellow);
	s.setOrigin(5, 5);

	target.draw(s, states);
}