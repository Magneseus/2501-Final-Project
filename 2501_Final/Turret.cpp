
#include "Turret.h"

Turret::Turret(vec::Vector2 p, Weapon* w, float min, float max) {
	position = p;
	main = w;

	if (max == 0) max = 360;

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

	friendlyTags.push_back(getTag());
	friendlyTags.push_back("Boss");
}

Turret::Turret(vec::Vector2 p, Weapon* w, float min, float max, std::function<void()> callback) : 
	Turret(p, w, min, max) {

	deathCallback = callback;
}

Turret::~Turret() {}

void Turret::update(const sf::Time& delta) {
	if (state == FRENZIED) {
		if (frenzyTimer.getElapsedTime().asSeconds() > 0.5) {
			if (std::rand() % 100 > 50) sign = (sign == -1) ? 1 : -1;
			frenzyTimer.restart();
			if (std::rand() % 100 < 5) {
				std::cout << Global::getState() << std::endl;
				if (deathCallback && !Global::GAMEOVER) deathCallback();	// don't call death callback until actually dead
				delObjectStatic(this);
			}
		}

		rotation += delta.asSeconds() * rotateSpeed * sign;

		main->shoot(toRadians(rotation), position, friendlyTags);
	} else if (state == ACTIVE) {
		target = enemy->getPosition();

		float prevRotation = rotation;
		Entity::update(delta);

		if (rotation > maxRotation || rotation < minRotation) {
			rotation = prevRotation;
		}

		main->shoot(toRadians(rotation), position, friendlyTags);
	} else {
		// do we keep turning?
		if (rotation > maxRotation) {
			sign = -1;
		}
		else if (rotation < minRotation) {
			sign = 1;
		}

		// turn
		rotation += delta.asSeconds() * rotateSpeed * sign;

		// do we see the player?
		// do you see what I see
		vec::Vector2 toPlayer(Global::player->getPosition().getX(), Global::player->getPosition().getY());
		toPlayer -= this->getPosition();

		if (toPlayer.getMag() < 300) {
			vec::Vector2 sightCone(toRadians(rotation));
			if (vec::angleBetween(sightCone, toPlayer) < toRadians(20)) {
				changeState(ACTIVE);
				enemy = Global::player;
			}
		}
	}

	s->update(delta);
	s->setRotation(rotation);
}

void Turret::changeState(int newState) {
	state = newState;
	s->changeState(newState);

	if (state == ACTIVE) {
		rotateSpeed = activeRotateSpeed;

		enemy = Global::player;
	}
	else if (state == IDLE) {
		rotateSpeed = idleRotateSpeed;
	}
	else if (state == FRENZIED) {
		rotateSpeed = activeRotateSpeed*2;
	}
}

void Turret::takeDamage(float damage) {
		if(state == IDLE) changeState(ACTIVE);

		Entity::takeDamage(damage);
}

void Turret::onDeath() {
	if (state == FRENZIED) return; // don't keep dying

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