#pragma once

#include <vector>
#include "Vector.h"

// Types of shapes
enum SHAPETYPE { RECT, CIRC, COUNT };

// Virtual class to represent a base Shape
class Shape
{
public:
	virtual ~Shape() = 0;

	virtual bool collide(const Shape&) const;
	
	virtual void move(const vec::Vector2&);
	virtual void setPos(const vec::Vector2&);
	virtual vec::Vector2& getPos() const;
	
	int getType() const { return static_cast<int>(_type); }
	SHAPETYPE getTypeEnum() const { return _type; }

protected:
	SHAPETYPE _type;
};

class Rect : public Shape
{
public:
	Rect(const vec::Vector2&, const vec::Vector2&);
	Rect(const vec::Vector2&, const vec::Vector2&, const vec::Vector2&, const vec::Vector2&);
	~Rect();

	virtual bool collide(const Shape&) const;

	virtual void setPos(const vec::Vector2&);
	virtual vec::Vector2& getPos() const;
	float getRad() const;

	virtual void move(const vec::Vector2&);
	void rotate(float);
	void rotateTo(float);

	bool pointInRect(const vec::Vector2&) const;

	vec::Vector2  tl, tr, bl, br;

private:
	float areaOf(const vec::Vector2&, const vec::Vector2&, const vec::Vector2&) const;
	void calcRad() const;

	vec::Vector2 center;
	float radius, angle;

};

class Circ : public Shape
{
public:
	Circ(const vec::Vector2&, float);
	~Circ();

	virtual bool collide(const Shape&) const;

	virtual void move(const vec::Vector2&);
	virtual void setPos(const vec::Vector2&);
	virtual vec::Vector2& getPos() const;
	float getRad() const;

private:
	vec::Vector2 pos;
	float radius;

};