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
#include "Debug.h"
#include "SpriteSheet.h"

class Entity;

// Some weird name-space stuff for static access to mouse co-ordinates
class Global
{
public:
	static sf::Vector2i mouseWindowCoords;
	static sf::Vector2i middleWindowCoords;
	static sf::Font niceFont;

	static SpriteSheet* globalSpriteSheet;

	static Entity* player;

	static bool SPAWNING;
	static bool FINISHEDSPAWN;

	static bool DEBUG;
};

/*                   	GAME OBJECT
	The base game object. All GameObjects will have a transform.
*/
class GameObject
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

	// Getter & Setters for position/rotation
	vec::Vector2 getPosition() { return position; }
	void setPosition(vec::Vector2 _position) { position = _position; }
	double getRotation() { return rotation; }
	void setRotation(double _rotation) { rotation = _rotation; }

	// Functions for addingObjects on the fly
	static void addObjectStatic(GameObject* go)
	{
		staticGameObjects.push_back(go);
	}

	static void delObjectStatic(GameObject* go)
	{
		staticGameObjectsDel.push_back(go);
	}

	static void remObjectStatic(GameObject* go)
	{
		staticGameObjectsRem.push_back(go);
	}

protected:
	vec::Vector2 position;
	double rotation;

	bool should_remove = false;
	int gameObjectType = 0;

private:
	static std::vector<GameObject*> staticGameObjects;
	static std::vector<GameObject*> staticGameObjectsDel;
	static std::vector<GameObject*> staticGameObjectsRem;

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

	virtual void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const {};

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

/*						COLLIDABLE
	All objects of this type must contain a Collider.
	Also must implement a collide(Collidable& other) function.

	TODO: Make a Collider
*/
class Collidable : public Updatable
{
public:
	Collidable() { gameObjectType |= 0b100; }
	virtual ~Collidable() {};

	virtual void onCollide(Collidable& other) = 0;

	virtual void update(const sf::Time& delta)
	{
		col.moveTo(getPosition());
		col.rotateTo(toRadians(getRotation()));
	}

	// Collides two hitboxes together
	static bool collide(Collidable& c1, Collidable& c2, vec::Vector2& normal = vec::Vector2())
	{
		return c1.col.collide(c2.col, normal);
	}

	// Pushes a hitbox by a normal
	static void collideBody(Collidable& c, vec::Vector2& normal)
	{
		if (!c.isStatic())
		{
			/*
			vec::Vector2 push = (*colA)->getPosition() - (*colA)->prevPos;
			push.setMag(1);
			push *= -1;

			vec::Vector2 normal = (*colA)->getPosition() - (*colB)->getPosition();

			// Check if the push vector is in the opposite direction from the center
			if (push.angleBetween(normal) > 90)
			push *= -1;
			else
			(*colA)->setPosition((*colA)->prevPos);

			(*colA)->setPosition((*colA)->getPosition() + push);
			*/

			c.setPosition(c.getPosition() + normal);
		}
	}

	const sf::String getTag() const { return tag; }
	void setTag(sf::String& newTag) { tag = newTag; }
	
	bool isSolid() { return solid; }
	bool isStatic() { return staticObject; }
	void setSolid(bool _solid) { solid = _solid; }
	void setStatic(bool _static) { staticObject = _static; }

	// Returns the hitbox of it's collider
	sf::FloatRect getAABB() const { return col.getAABB(); }

	vec::Vector2 prevPos;

protected:
	sf::String tag;
	Collider col;

private:
	bool solid;
	bool staticObject;
};

/*						ENTITY
	This object will comprise the majority of in-game objects.
	It will have all three of the above components.
*/
class Entity : public Drawable, public Collidable
{
public:
	virtual ~Entity() {};
	void update(const sf::Time& delta);

	virtual void takeDamage(float amount, Entity* source);
	virtual void debugDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	vec::Vector2 vel;

protected:
	float accelRate, topSpeed, rotateSpeed, dragValue;	// per second
	bool brakesOn = false;

	Entity* enemy;	// entity's enemy, who's it trying to shoot at
	vec::Vector2 target; // where the entity wants to be looking

	float maxHealth = 100;
	float curHealth = 100;

	void drawHealthBar(sf::RenderTarget& w, sf::RenderStates s) const;

	sf::Clock healthBarTimer;

	virtual void onDeath(Entity* source) = 0;

	enum MOVEMENT { FORWARD = 1, REVERSE = -1, STILL = 0,
					CLWISE = 1, COCLWISE = -1, LEFT = -1, RIGHT = 1 };

	int motion, turning, strafe;
};