#pragma once

/*
	This file contains the definitions of the various Game Objects within our game.
	(Renderable, Updatable, etc.)
	 - GameObject
	 |-> Updatable
	 |-> Collidable
	 |-> Drawable
	 |
	 | |-> Entity (All three)
*/

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\String.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Vector.h"
#include "Collider.h"

// Some weird name-space stuff for static access to mouse co-ordinates
class Global
{
public:
	static sf::Vector2i mouseWindowCoords;
};

/*                   	GAME OBJECT
	The base game object. All GameObjects will have a transform.
*/
class GameObject : public sf::Transformable
{
	friend class Controller;

public:
	virtual ~GameObject() {};
	
	//  Functions for erase()
	bool removeFunc() { return should_remove; }
	void deleteObject() { should_remove = true; }

	// Functions for checking type
	bool isUpdatable()  { return (gameObjectType & 0b001) == 1; }
	bool isDrawable()   { return (gameObjectType & 0b010) >> 1 == 1; }
	bool isCollidable() { return (gameObjectType & 0b100) >> 2 == 1; }
	bool isNone()       { return gameObjectType == 0; }

	// Functions for manipulating type
	void andType(int x) { gameObjectType &= x; }


	// Functions for addingObjects on the fly
	static void addObjectStatic(GameObject* go)
	{
		staticGameObjects.push_back(go);
	}

	static void delObjectStatic(GameObject* go)
	{
		staticGameObjectsDel.push_back(go);
	}

protected:
	bool should_remove = false;
	int gameObjectType = 0;

private:
	static std::vector<GameObject*> staticGameObjects;
	static std::vector<GameObject*> staticGameObjectsDel;

};

/*                    	UPDATABLE
	All objects of this type must implement an update(sf::Time) method.
*/
class Updatable : public virtual GameObject
{
public:
	Updatable() { gameObjectType |= 0b001; };
	virtual ~Updatable() {};
	virtual void update(const sf::Time&) = 0;
};

/*                      DRAWABLE
	All objects of this type must implement a draw() function.
*/
class Drawable : public virtual GameObject, public sf::Drawable
{
public:
	Drawable() { gameObjectType |= 0b010; };
	virtual ~Drawable() {};

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

/*						COLLIDABLE
	All objects of this type must contain a Collider.
	Also must implement a collide(Collidable& other) function.

	TODO: Make a Collider
*/
class Collidable : public virtual GameObject
{
public:
	Collidable() { gameObjectType |= 0b100; }
	virtual ~Collidable() {};
	virtual void onCollide(const Collidable& other) = 0;
	
	// Collides two hitboxes together
	static bool collide(const Collidable& c1, const Collidable& c2)
	{
		return c1.col.collide(c2.col);
	}

	const sf::String getTag() const { return tag; }
	void setTag(sf::String& newTag) { tag = newTag; }

protected:
	sf::String tag;
	Collider col;
};

/*						ENTITY
	This object will comprise the majority of in-game objects.
	It will have all three of the above components.
*/
class Entity : public Drawable, public Updatable, public Collidable
{
public:
	virtual ~Entity() {};
};