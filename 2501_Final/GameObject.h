#pragma once

/*
	This file contains the definitions of the various Game Objects within our game.
	(Renderable, Updateable, etc.)
	 - GameObject
	 |-> Updateable
	 |-> Collideable
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



/*                   	GAME OBJECT
	The base game object. All GameObjects will have a transform.
*/
class GameObject : public sf::Transformable
{
public:
	virtual ~GameObject();
	
	//  Functions for erase()
	bool removeFunc() { return should_remove; }
	void deleteObject() { should_remove = true; }

protected:
	bool should_remove = false;
};

/*                    	UPDATEABLE
	All objects of this type must implement an update(sf::Time) method.
*/
class Updateable : public GameObject
{
public:
	virtual ~Updateable();
	virtual void update(const sf::Time&) = 0;
};

/*                      DRAWABLE
	All objects of this type must implement a draw() function.
*/
class Drawable : public GameObject, public sf::Drawable
{
public:
	virtual ~Drawable();
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

/*						COLLIDEABLE
	All objects of this type must contain a Collider.
	Also must implement a collide(Collideable& other) function.

	TODO: Make a Collider
*/
class Collideable : public GameObject
{
public:
	virtual ~Collideable();
	virtual void onCollide(const Collideable& other) = 0;

	const sf::String getTag() const { return tag; }
	void setTag(sf::String& newTag) { tag = newTag; }

protected:
	sf::String tag;
};

/*						ENTITY
	This object will comprise the majority of in-game objects.
	It will have all three of the above components.
*/
class Entity : public Drawable, public Updateable, public Collideable
{
public:
	virtual ~Entity();
};