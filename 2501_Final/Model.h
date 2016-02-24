#pragma once

#include "GameObject.h"
#include <SFML\System.hpp>

class Model
{
public:
	Model();
	~Model();
	
	void update(const sf::Time&);
	void addUpdatable(Updatable*);
	bool delUpdatable(Updatable*);
	void addCollidable(Collidable*);
	bool delCollidable(Collidable*);
	
private:
	std::vector<Updatable*> updatables;
	std::vector<Collidable*> collidables;
	
};