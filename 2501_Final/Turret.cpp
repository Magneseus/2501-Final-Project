
#include "Turret.h"

Turret::Turret(vec::Vector2 p, Weapon* w, float min, float max) {
	position = p;
	main = w;

	minRotation = min;
	maxRotation = max;

	rotation = minRotation + std::rand() % maxRotation;
	
	SpriteSheet* temp = new SpriteSheet(sf::String("img/test.png"));
	s = new AnimatedSprite(temp, 10);
	s->setPosition(position);

	std::vector<sf::String> names;

	names.push_back("smallturret_idle.png");
	s->addState(names);
	names.clear();

	names.push_back("smallturret_active.png");
	s->addState(names);
	names.clear();

	names.push_back("smallturret_off.png");
	names.push_back("smallturret_active.png");
	s->addState(names);
	names.clear();

	/*i.loadFromFile("img/smallturret_idle.png");
	a.loadFromFile("img/smallturret_active.png");
	s.setOrigin(16, 16);
	s.setPosition(position.getSfVec());
	s.setTexture(i);
	*/
	Rect* r = new Rect(vec::Vector2(-15, -15), vec::Vector2(25, 15));
	col.addShape(r);
	col.moveTo(position);

	changeState(IDLE);
}

Turret::~Turret() {}

void Turret::update(const sf::Time& delta) {
	//Entity::update(delta);

	if (state == FRENZIED) {
		if (frenzyTimer.getElapsedTime().asSeconds() > 0.5) {
			if (std::rand() % 100 > 50) sign = (sign == -1) ? 1 : -1;
			frenzyTimer.restart();
		}
	} else {
		if (rotation > maxRotation) {
			sign = -1;
		}
		else if (rotation < minRotation) {
			sign = 1;
		}
	}

	rotation += delta.asSeconds() * rotateSpeed * sign;

	s->update(delta);
	s->setRotation(rotation);

	main->shoot(toRadians(rotation), position);
}

void Turret::changeState(int newState) {
	state = newState;
	s->changeState(newState);
	if (state == ACTIVE) {
		rotateSpeed = activeRotateSpeed;
	}
	else if (state == IDLE) {
		rotateSpeed = idleRotateSpeed;
	}
	else if (state == FRENZIED) {
		rotateSpeed = activeRotateSpeed*2;
	}
}

void Turret::onCollide(Collidable& other) {
}

void Turret::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*s, states);
	target.draw(col, states);
}