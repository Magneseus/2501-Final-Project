#pragma once

#include "GameObject.h"
#include "Weapon.h"
#include "Turret.h"

class Mainframe : public Entity {
public:
	Mainframe();
	~Mainframe();

	virtual void update(const sf::Time&);
	virtual void onCollide(Collidable& other);

	sf::Sprite computer;
	sf::Texture compTexture;

	virtual void takeDamage(float amount);

private:
	virtual void onDeath();

	enum STATES {HEALTHY, DAMAGED, DYING};
	int state;

	sf::Clock turretSpawnTimer;
	int numSpawnedTurrets = 0;

	void turretHasDied();

	void spawnTurret();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};