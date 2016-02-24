#include "Model.h"

Model::Model()
{
	Player p;

	std::cout << std::endl << p.isUpdatable()
		<< " " << p.isDrawable()
		<< " " << p.isCollidable();
}

Model::~Model()
{
	
}

void Model::update(const sf::Time& delta)
{
	// Check collidables for invalid objects
	for (auto it = collidables.begin(); it != collidables.end(); )
	{
		if ((*it)->removeFunc())
			it = collidables.erase(it);
		else
			++it;
	}

	// Collide all objects
	for (auto colA = collidables.begin(); colA != collidables.end(); ++colA)
	{
		// Otherwise, collide with all other objects
		for (auto colB = colA; colB != collidables.end(); ++colB)
		{
			// If they are determined to be colliding, call the callback function for both
			if (Collidable::collide(**colA, **colB))
			{
				(*colA)->onCollide(**colB);
				(*colB)->onCollide(**colA);
			}
		}
	}

	// Update all the updateables
	for (auto it = updatables.begin(); it != updatables.end(); )
	{
		// Check if it needs to be removed
		if ((*it)->removeFunc())
		{
			it = updatables.erase(it);
		}
		else
		{
			if (*it != NULL)
				(*it)->update(delta);
			++it;
		}

	}
}




//      GETTERS & SETTERS      //


/*
This function simply adds a Updatable object to the list to be rendered.
*/
void Model::addUpdatable(Updatable* u)
{
	updatables.push_back(u);
}

/*
This function removes a Updatable object from our render list.

Return:
- true: The object was stored in our list, and was flagged to be removed
- false: The object wasn't stored in our list, not flagged for removal
*/
bool Model::delUpdatable(Updatable* u)
{
	bool contains = false;
	for (auto it = updatables.begin(); it != updatables.end() && !contains; it++)
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

/*
This function simply adds a Collidable object to the list to be rendered.
*/
void Model::addCollidable(Collidable* u)
{
	collidables.push_back(u);
}

/*
This function removes a Collidable object from our render list.

Return:
- true: The object was stored in our list, and was flagged to be removed
- false: The object wasn't stored in our list, not flagged for removal
*/
bool Model::delCollidable(Collidable* u)
{
	bool contains = false;
	for (auto it = collidables.begin(); it != collidables.end() && !contains; it++)
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