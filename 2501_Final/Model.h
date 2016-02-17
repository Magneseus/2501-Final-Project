#pragma once

#include "GameObject.h"
#include <SFML\System.hpp>

class Model
{
public:
	Model();
	~Model();
	
	void update(const sf::Time&);
	void addUpdateable(Updateable*);
	bool delUpdateable(Updateable*);
	
private:
	std::vector<Updateable*> updateables;
	
};