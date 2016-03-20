#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Vector.h"

// Types of shapes
enum SHAPETYPE { RECT, CIRC, COUNT };

// Virtual class to represent a base Shape
class Shape : public sf::Drawable
{
public:
	virtual ~Shape() {};

	virtual bool collide(const Shape*, vec::Vector2& normal) const = 0;
	
	virtual void move(const vec::Vector2&) = 0;
	virtual void setPos(const vec::Vector2&) = 0;
	virtual vec::Vector2 getPos() const = 0;
	virtual float getRad() const = 0;
	virtual sf::FloatRect getAABB() const = 0;
	
	int getType() const { return static_cast<int>(_type); }
	SHAPETYPE getTypeEnum() const { return _type; }

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	SHAPETYPE _type;
};

class Rect : public virtual Shape
{
public:
	Rect(const vec::Vector2&, const vec::Vector2&);
	Rect(const vec::Vector2&, const vec::Vector2&, const vec::Vector2&, const vec::Vector2&);
	~Rect();

	virtual bool collide(const Shape*, vec::Vector2& normal) const;

	virtual void setPos(const vec::Vector2&);
	virtual vec::Vector2 getPos() const;
	virtual float getRad() const;
	virtual sf::FloatRect getAABB() const;

	virtual void move(const vec::Vector2&);
	void rotate(float);
	void rotateTo(float);

	bool pointInRect(const vec::Vector2&) const;
	bool pointInRect(const vec::Vector2& point, vec::Vector2& normal) const;

	vec::Vector2  tl, tr, bl, br;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float areaOf(const vec::Vector2&, const vec::Vector2&, const vec::Vector2&) const;
	void calcRad();

	float minVal(float a, float b, float c, float d) const;
	float maxVal(float a, float b, float c, float d) const;

	vec::Vector2 center;
	float radius, angle;

};

class Circ : public virtual Shape
{
public:
	Circ(const vec::Vector2&, float);
	~Circ();

	virtual bool collide(const Shape*, vec::Vector2& normal) const;

	virtual void move(const vec::Vector2&);
	virtual void setPos(const vec::Vector2&);
	virtual vec::Vector2 getPos() const;
	virtual float getRad() const;
	virtual sf::FloatRect getAABB() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	vec::Vector2 pos;
	float radius;

};

// Some global functions
bool collideRC(const Rect&, const Circ&, vec::Vector2&);
bool lineIntCirc(const vec::Vector2&, const vec::Vector2&, const Circ&, vec::Vector2&);