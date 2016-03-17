#include "QuadTree.h"

QuadTree::QuadTree(int _depth, sf::FloatRect _bounds)
	: depth(_depth),
	bounds(_bounds)
{
	nodes = new QuadTree*[4];
	for (int i = 0; i < 4; ++i)
		nodes[i] = NULL;
}

QuadTree::~QuadTree()
{
	clear();
}


void QuadTree::add(Collidable* col)
{
	// Check if we have children
	if (nodes[0] != NULL)
	{
		int insertInd = getInd(col);

		// If it belongs in the children, add it there
		if (insertInd != -1)
		{
			nodes[insertInd]->add(col);
			return;
		}
	}

	// Otherwise we add it to the current node
	cols.push_back(col);

	// Check if we have overflow but are still under the max level depth
	if (cols.size() > MAX_COL && depth < MAX_DEPTH)
	{
		if (nodes[0] == NULL)
			split();

		for (auto it = cols.begin(); it != cols.end(); )
		{
			int insertInd = getInd(*it);
			
			// If it can be added to a child node, add it there
			if (insertInd != -1)
			{
				Collidable* c = *it;
				nodes[insertInd]->add(c);

				it = cols.erase(it);
			}
			// Otherwise continue
			else
			{
				++it;
			}
		}
	}
}

std::vector<Collidable*>& QuadTree::getList(std::vector<Collidable*>& curList, Collidable* col)
{
	if (nodes[0] != NULL)
	{
		int ind = getInd(col);

		// If we have children, and the object would belong in a child retrieve it's list
		if (ind != -1)
			nodes[ind]->getList(curList, col);
	}

	// Add all the elements from the current node
	curList.insert(curList.end(), cols.begin(), cols.end());

	return curList;
}

int QuadTree::getInd(Collidable* col)
{
	int retInd = -1;
	
	sf::FloatRect aabb = col->getAABB();
	sf::Vector2f middle = sf::Vector2f(bounds.left + (bounds.width / 2.0f),
			bounds.top + (bounds.height / 2.0f));
	
	bool topQuads = aabb.top + aabb.height < middle.y;
	bool bottomQuads = aabb.top > middle.y;

	if (aabb.left + aabb.width < middle.x)
	{
		if (topQuads)
			retInd = 1;
		else if (bottomQuads)
			retInd = 2;
	}
	else if (aabb.left > middle.x)
	{
		if (topQuads)
			retInd = 0;
		else if (bottomQuads)
			retInd = 3;
	}

	return retInd;
}

void QuadTree::split()
{
	float x = bounds.left;
	float y = bounds.top;
	float w = bounds.width / 2.0f;
	float h = bounds.height / 2.0f;

	// Add the new nodes
	nodes[0] = new QuadTree(depth + 1, sf::FloatRect(x + w, y, w, h));
	nodes[1] = new QuadTree(depth + 1, sf::FloatRect(x, y, w, h));
	nodes[2] = new QuadTree(depth + 1, sf::FloatRect(x, y + h, w, h));
	nodes[3] = new QuadTree(depth + 1, sf::FloatRect(x + w, y + h, w, h));
}

void QuadTree::clear()
{
	cols.clear();

	for (int i = 0; i < 4; ++i)
	{
		if (nodes[i] != NULL)
		{
			nodes[i]->clear();

			delete nodes[i];
			nodes[i] = NULL;
		}
	}
}
