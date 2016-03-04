#pragma once

#include <vector>
#include "Vector.h"

// Types of shapes
enum SHAPETYPE { RECT, CIRC, COUNT };

// Virtual class to represent a base Shape
class Shape
{
public:
	virtual ~Shape() {}

	bool collide(const Shape&) const;
	int type() const;
	void move(const vec::Vector2&);
	vec::Vector2& getPos() const;
	void setPos(vec::Vector2);

private:
	SHAPETYPE _type;
};

