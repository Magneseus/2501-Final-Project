#include "Model.h"

Model::Model()
{
	collisionTree = new QuadTree(0, sf::FloatRect(-1000, -1000, 2000, 2000));
}

Model::~Model()
{
	delete collisionTree;
}

void Model::update(const sf::Time& delta)
{
	// Check collidables for invalid objects
	for (auto it = collidables.begin(); it != collidables.end(); )
	{
		if ((*it)->removeFunc())
		{
			(*it)->andType(0b110);
			it = collidables.erase(it);
		}
		else
			++it;
	}

	// Update all the updateables
	for (auto it = updatables.begin(); it != updatables.end(); )
	{
		// Check if it needs to be removed
		if ((*it)->removeFunc())
		{
			(*it)->andType(0b011);
			it = updatables.erase(it);
		}
		else
		{
			if (*it != NULL)
			{
				// Check if it's collidable and needs to be updated
				Collidable* c = NULL;
				if ((*it)->isCollidable())
					c = dynamic_cast<Collidable*>(*it);

				if (c != NULL)
				{
					c->prevPos = c->getPosition();
				}

				(*it)->update(delta);

				if (c != NULL)
					(*c).Collidable::update(delta);
			}
			++it;
		}

	}

	// Add objects to the quadtree
	collisionTree->clear();
	for (auto it = collidables.begin(); it != collidables.end(); ++it)
		collisionTree->add(*it);


	// Iterate through objects
	std::vector<Collidable*> possibleCollisions;
	for (auto colA = collidables.begin(); colA != collidables.end(); ++colA)
	{
		possibleCollisions.clear();
		collisionTree->getList(possibleCollisions, *colA);

		for (auto colB = possibleCollisions.begin(); colB != possibleCollisions.end(); ++colB)
		{
			// Normal vector of collision
			vec::Vector2 colNormal;

			// If they are determined to be colliding, call the callback function for both
			if (*colA != *colB && Collidable::collide(**colA, **colB, colNormal))
			{
				// Move objects if required
				if ((*colA)->isSolid() && (*colB)->isSolid())
				{
					Collidable::collideBody(**colA, colNormal);
					
					// If we can update the object, set its velocity to 0
					if ((*colA)->isUpdatable())
					{
						Entity* entA = dynamic_cast<Entity*>(*colA);
						if (entA != NULL)
						{
							entA->vel.setMag(0);
						}
					}
					
				}

				(*colA)->onCollide(**colB);
			}
		}
	}
}




//      GETTERS & SETTERS      //


/*
This function simply adds a Updatable object to the list to be rendered.
*/
void Model::addUpdatable(Updatable* u)
{
	// If we have a null pointer, don't add it to the list
	if (!u) return;

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
		{
			contains = true;
			break;
		}
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
	{
		u->deleteObject();
		u->andType(0b011);
	}

	// Tell them if we had an object stored and flagged it
	return contains;
}

bool Model::remUpdatable(Updatable* u)
{
	for (auto it = updatables.begin(); it != updatables.end(); it++)
	{
		// Object was found
		if (*it == u)
		{
			updatables.erase(it);
			return true;
		}
	}

	return false;
}

/*
This function simply adds a Collidable object to the list to be rendered.
*/
void Model::addCollidable(Collidable* u)
{
	// If we have a null pointer, don't add it to the list
	if (!u) return;

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
		{
			contains = true;
			break;
		}
	}

	// If we have a pointer to the object stored, "delete" it
	if (contains)
	{
		u->deleteObject();
		u->andType(0b110);
	}

	// Tell them if we had an object stored and flagged it
	return contains;
}

bool Model::remCollidable(Collidable* u)
{
	for (auto it = collidables.begin(); it != collidables.end(); it++)
	{
		// Object was found
		if (*it == u)
		{
			collidables.erase(it);
			return true;
		}
	}

	return false;
}