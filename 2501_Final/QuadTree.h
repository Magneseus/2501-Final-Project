#pragma once

#include <SFML\Graphics\Rect.hpp>
#include <vector>
#include "GameObject.h"

class QuadTree
{
public:
	QuadTree(int _depth, sf::FloatRect _bounds);
	~QuadTree();

	void clear();
	void add(Collidable* col);
	std::vector<Collidable*>& getList(std::vector<Collidable*>& curList, Collidable* col);

private:
	void split();
	int getInd(Collidable* col);

	const int MAX_COL = 5;
	const int MAX_DEPTH = 20;

	int depth;
	std::vector<Collidable*> cols;
	sf::FloatRect bounds;
	QuadTree** nodes;

};