
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

	state = HEALTHY;

	setTag(sf::String("Boss"));
}

Mainframe::~Mainframe() {}

void Mainframe::takeDamage(float amount) {
	Entity::takeDamage(amount);
}

void Mainframe::update(const sf::Time&) {
	computer.setRotation(90);
	computer.setPosition(position.getSfVec());

	float hpPercent = curHealth / maxHealth;

	if (hpPercent < .1) {
		state = DYING;
	} else if (hpPercent < .75) {
		state = DAMAGED;
	} else {
		state = HEALTHY;
	}

	if (state == DYING) {
		if (turretSpawnTimer.getElapsedTime().asSeconds() > 5 && numSpawnedTurrets < 2) {
			turretSpawnTimer.restart();
			spawnTurret();
		}
	} else if (state == DAMAGED) {
		if (turretSpawnTimer.getElapsedTime().asSeconds() > 5 && numSpawnedTurrets < 2) {
			turretSpawnTimer.restart();
			spawnTurret();
		}
	} else if (state == HEALTHY) {

	}
}

void Mainframe::spawnTurret() {
	// find position (in range, not colliding with self)

	vec::Vector2 tempPos(this->getPosition().getX()-200, this->getPosition().getY());

	// make weapon

	Weapon* tempWeapon = new Weapon(1, 15, 250);

	// make turret (with callback)

	Turret* tempTurret = new Turret(tempPos, tempWeapon, 0, 0, std::bind(&Mainframe::turretHasDied, this));

	tempTurret->changeState(Turret::ACTIVE);
	 
	// increment, and add turret

	numSpawnedTurrets++;

	addObjectStatic(tempTurret);
}

void Mainframe::turretHasDied() {
	std::cout << "Turret is ded" << std::endl;
	numSpawnedTurrets--;
}

void Mainframe::onCollide(Collidable& other) { // nothing 
}

void Mainframe::onDeath() { Global::setState(Global::S_WIN); delObjectStatic(this); }

void Mainframe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(computer, states);
	drawHealthBar(target, states);
}