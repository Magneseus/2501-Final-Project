
#include "Turret.h"

Turret::Turret(vec::Vector2 p, Weapon* w, float min, float max) {
	position = p;
	main = w;

	minRotation = min;
	maxRotation = max;

	rotation = minRotation + std::rand() % maxRotation;
	
	s = new AnimatedSprite(Global::globalSpriteSheet, 10);
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

	changeState(IDLE);

	/*i.loadFromFile("img/smallturret_idle.png");
	a.loadFromFile("img/smallturret_active.png");
	s.setOrigin(16, 16);
	s.setPosition(position.getSfVec());
	s.setTexture(i);
	*/
	Rect* r = new Rect(vec::Vector2(-15, -15), vec::Vector2(25, 15));
	col.addShape(r);
	col.moveTo(position);

	setTag(sf::String("Turret"));
}

Turret::~Turret() {}

void Turret::update(const sf::Time& delta) {
	if (state == FRENZIED) {
		if (frenzyTimer.getElapsedTime().asSeconds() > 0.5) {
			if (std::rand() % 100 > 50) sign = (sign == -1) ? 1 : -1;
			frenzyTimer.restart();
			if (std::rand() % 100 < 5) delObjectStatic(this);
		}

		rotation += delta.asSeconds() * rotateSpeed * sign;

		main->shoot(toRadians(rotation), position, this);
	} else if (state == ACTIVE) {
		target = enemy->getPosition();

		float prevRotation = rotation;
		Entity::update(delta);

		if (rotation > maxRotation || rotation < minRotation) {
			rotation = prevRotation;
		}


		main->shoot(toRadians(rotation), position, this);
	} else {
		if (rotation > maxRotation) {
			sign = -1;
		}
		else if (rotation < minRotation) {
			sign = 1;
		}

		rotation += delta.asSeconds() * rotateSpeed * sign;
	}

	s->update(delta);
	s->setRotation(rotation);
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

void Turret::takeDamage(float damage, Entity* source) {
	changeState(ACTIVE);

	enemy = source;

	Entity::takeDamage(damage, source);
}

void Turret::onDeath(Entity* killer) {
	changeState(FRENZIED);
}

void Turret::onCollide(Collidable& other) {}

void Turret::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*s, states);

	drawHealthBar(target, states);
	
	if (Global::DEBUG)
	{
		if (enemy != NULL) {
			sf::VertexArray l;
			l.setPrimitiveType(sf::Lines);
			l.resize(2);

			l[0].position.x = position.getX();
			l[0].position.y = position.getY();
			l[0].color = sf::Color::Green;

			l[1].position.x = enemy->getPosition().getX();
			l[1].position.y = enemy->getPosition().getY();
			l[1].color = sf::Color::Green;

			target.draw(l, states);
		}
	}
}