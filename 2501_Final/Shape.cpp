#include "Shape.h"

//////////////////////////////////////
//            RECTANGLE             //
//////////////////////////////////////

// Axis-aligned Rectangle
Rect::Rect(const vec::Vector2& _tl, const vec::Vector2& _br)
	: tl(_tl),
	br(_br),
	tr(br.getX(), tl.getY()),
	bl(tl.getX(), br.getY()),

	angle(0.0f)
{
	// Set the type
	_type = RECT;

	// Get the max width of the rectangle
	vec::Vector2 r = tl - br;
	radius = r.getMag();

	// Set the center of the rectangle
	center = tl + (r / 2);
}

// Non-axis aligned Rectangle
Rect::Rect(const vec::Vector2& _tl, const vec::Vector2& _tr,
			const vec::Vector2& _br, const vec::Vector2& _bl)
	: tl(_tl),
	tr(_tr),
	br(_br),
	bl(_bl),

	angle(0.0f)
{
	// Set the type
	_type = RECT;

	// Get the longest section of the rectangle
	vec::Vector2 lengths[6];
	lengths[0] = tr - tl;
	lengths[1] = br - tr;
	lengths[2] = bl - br;
	lengths[3] = tl - bl;
	lengths[4] = br - tl;
	lengths[5] = bl - tr;

	int ind = 0;
	radius = 0.0f;

	for (int i = 0; i < 6; i++)
	{
		double len = lengths[i].getMag();
		
		if (len > radius)
		{
			radius = len;
			ind = i;
		}
	}

	// Set the center of mass
	center = (tl + tr + bl + br) / 2;
}



/////////////////////////////////////////
//              CIRCLE                 //
/////////////////////////////////////////

// Assumes pos is the center of the circle
// radius is obviously the radius
Circ::Circ(const vec::Vector2& _pos, float _radius)
	: pos(_pos),
	radius(_radius)
{

}




/////////////////////////////////////////
//          GLOBAL FUNCTIONS           //
/////////////////////////////////////////

bool lineIntCirc(const vec::Vector2& p1, const vec::Vector2 p2, const Circ& c)
{
	bool isInt = false;

	//Line seg.
	vec::Vector2 x1 = p2 - p1;

	//c - p1
	vec::Vector2 x2 = c.getPos() - p1;
	//c - p2
	vec::Vector2 x3 = c.getPos() - p2;

	float theta1 = x1.angleBetween(x2);

	vec::Vector2 x4 = x1 * -1;
	float theta2 = x4.angleBetween(x3);

	if (theta1 > 3.141592653589793f / 2)
	{
		float d = x2.getMag();
		if (d < c.getRad())
			isInt = true;
	}
	else if (theta2 > 3.141592653589793f / 2)
	{
		float d = x3.getMag();
		if (d < c.getRad())
			isInt = true;
	}
	else
	{
		float d = sin(theta1) * x2.getMag();
		if (d < c.getRad())
			isInt = true;
	}

	return isInt;
}

bool collideRC(Rect r, Circ c)
{
	// Check if they're near each other
	if (r.getPos().dist(c.getPos()) > r.getRad() + c.getRad())
		return false;

	// If they are, check all lines for intersection
	if (lineIntCirc(r.tl, r.tr, c))
		return true;
	if (lineIntCirc(r.tr, r.br, c))
		return true;
	if (lineIntCirc(r.br, r.bl, c))
		return true;
	if (lineIntCirc(r.bl, r.tl, c))
		return true;

	return false;
}