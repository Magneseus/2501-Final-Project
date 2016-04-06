#pragma once

#include "GameObject.h"
#include "QuadTree.h"
#include <SFML\System.hpp>

class Model
{
public:
	Model();
	~Model();
	
	void update(const sf::Time&);
	void addUpdatable(Updatable*, bool addBack=false);
	bool delUpdatable(Updatable*);
	bool remUpdatable(Updatable*);

	void addCollidable(Collidable*, bool addBack=false);
	bool delCollidable(Collidable*);
	bool remCollidable(Collidable*);
	
private:
	std::vector<Updatable*> updatables;
	std::vector<Collidable*> collidables;

	QuadTree* collisionTree;
	
};