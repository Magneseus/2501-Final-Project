
#include "Projectile.h"

Projectile::Projectile(std::vector<sf::String> safe, vec::Vector2 p, vec::Vector2 v, float dam, float speed) {
	friendlyTags = safe;

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
		onDeath();
	}
}

void Projectile::onDeath() { delObjectStatic(this); }

void Projectile::onCollide(Collidable& other) {
	if (other.getTag() == "Projectile") return;

	bool doDamage = true;

	Entity* temp = dynamic_cast<Entity*>(&other);
 
	if (temp == NULL) doDamage = false;

	for (int i = 0; i < friendlyTags.size(); i++) {
		if (other.getTag() == friendlyTags[i]) {
			return;
			//doDamage = false;
		}
	}

	if (doDamage) temp->takeDamage(damage);

	onDeath();
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::CircleShape s(5);
	s.setPosition(position.getSfVec());
	s.setFillColor(sf::Color::Yellow);
	s.setOrigin(5, 5);

	target.draw(s, states);
}