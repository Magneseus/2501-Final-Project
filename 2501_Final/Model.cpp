#include "Model.h"

Model::Model()
{
	
}

Model::~Model()
{
	
}

void Model::update(const sf::Time& delta)
{
	// Update all the updateables
	for (auto it = updateables.begin(); it != updateables.end(); )
	{
		// Check if it needs to be removed
		if ((*it)->removeFunc())
		{
			it = updateables.erase(it);
		}
		else
		{
			(*it)->update(delta);
			++it;
		}

	}
}

/*
This function simply adds a Updateable object to the list to be rendered.
*/
void Model::addUpdateable(Updateable* u)
{
	updateables.push_back(u);
}

/*
This function removes a Updateable object from our render list.

Return:
- true: The object was stored in our list, and was flagged to be removed
- false: The object wasn't stored in our list, not flagged for removal
*/
bool Model::delUpdateable(Updateable* u)
{
	bool contains = false;
	for (auto it = updateables.begin(); it != updateables.end() && !contains; it++)
	{
		// Object was found
		if (*it == u)
			contains = true;
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
		u->deleteObject();

	// Tell them if we had an object stored and flagged it
	return contains;
}