
#include "Mainframe.h"

Mainframe::Mainframe() {
	setSolid(true);
	setStatic(true);

	compTexture.loadFromFile("img/mastermind.png");

	computer.setTexture(compTexture);

	computer.setOrigin(121, 97);
	computer.setRotation(90);
	setRotation(90);

	Rect* r = new Rect(vec::Vector2(-121, -97), vec::Vector2(121, 97));
	col.addShape(r);

	col.rotateTo(toRadians(90));


	maxHealth = 500;
	curHealth = maxHealth;

	setTag(sf::String("Boss"));
}

Mainframe::~Mainframe() {}

void Mainframe::takeDamage(float amount, Entity* source) {
	if (source && source->getTag() != "Turret") {
		Entity::takeDamage(amount, source);
	}
}

void Mainframe::update(const sf::Time&) {
	computer.setRotation(90);
	computer.setPosition(position.getSfVec());
}

void Mainframe::onCollide(Collidable& other) { // nothing 
}

void Mainframe::onDeath(Entity* killer) { Global::WIN = true; delObjectStatic(this); }

void Mainframe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(computer, states);
	drawHealthBar(target, states);
}