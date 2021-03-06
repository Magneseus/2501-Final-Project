#include "Shape.h"

//////////////////////////////////////
//            RECTANGLE             //
//////////////////////////////////////

// Axis-aligned Rectangle
Rect::Rect(const vec::Vector2& _tl, const vec::Vector2& _br) : Rect(_tl, vec::Vector2(_br.getX(), _tl.getY()), _br, vec::Vector2(_tl.getX(), _br.getY()))
{
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
	center = (tl + tr + bl + br) / 4;
}

Rect::~Rect() {}



bool Rect::collide(const Shape* shape, vec::Vector2& normal) const
{
	// Check for a null-pointer
	if (shape == NULL)
		return false;

	bool isColliding = false;

	// If rect-rect collision
	if (shape->getTypeEnum() == RECT)
	{
		const Rect* r = dynamic_cast<const Rect*>(shape);

		// Check for a null cast
		if (r == NULL)
			return false;

		if (r->getPos().dist(this->getPos()) < getRad() + r->getRad())
		{
			//Check if any point lies inside the other rect
			if (pointInRect(r->tl, normal) || pointInRect(r->tr, normal) ||
				pointInRect(r->br, normal) || pointInRect(r->bl, normal))
				isColliding = true;

			if (r->pointInRect(tl, normal) || r->pointInRect(tr, normal) ||
				r->pointInRect(br, normal) || r->pointInRect(bl, normal))
				isColliding = true;
		}
	}
	// If rect-circ collision
	else if (shape->getTypeEnum() == CIRC)
	{
		const Circ* c = dynamic_cast<const Circ*>(shape);
		// Check for a null cast
		if (c == NULL)
			return false;

		isColliding = collideRC(*this, *c, normal);
	}

	return isColliding;
}


// Move the object by a specific vector
void Rect::move(const vec::Vector2& moveAmount)
{
	center += moveAmount;
	tl += moveAmount;
	tr += moveAmount;
	br += moveAmount;
	bl += moveAmount;
}

// Rotate the object by a specific angle (radians)
void Rect::rotate(float _angle)
{
	rotateTo(angle + _angle);
}

// Rotate the object to a specific angle (radians)
void Rect::rotateTo(float _angle)
{
	float d = _angle - angle;

	// Record old center
	vec::Vector2 _center = center;

	// Translate so center is at origin
	move(_center * -1);

	// Rotate all vectors
	tl.rotate(d);
	tr.rotate(d);
	br.rotate(d);
	bl.rotate(d);

	// Translate back
	move(_center);

	// Set angle
	angle = _angle;
}

bool Rect::pointInRect(const vec::Vector2& point) const
{
	bool colliding = true;

	//float rSum = tl.dist(tr) * tl.dist(bl);
	float rSum = areaOf(tl, tr, bl) + areaOf(tr, br, bl);

	float a1 = areaOf(tl, point, bl);
	float a2 = areaOf(bl, point, br);
	float a3 = areaOf(br, point, tr);
	float a4 = areaOf(point, tr, tl);

	float pSum = a1 + a2 + a3 + a4;

	if (pSum - rSum > 2)
		colliding = false;

	return colliding;
}

bool Rect::pointInRect(const vec::Vector2& point, vec::Vector2& normal) const
{
	//float rSum = tl.dist(tr) * tl.dist(bl);
	float rSum = areaOf(tl, tr, bl) + areaOf(tr, br, bl);

	float a1 = areaOf(tl, point, bl);
	float a2 = areaOf(bl, point, br);
	float a3 = areaOf(br, point, tr);
	float a4 = areaOf(point, tr, tl);

	float pSum = a1 + a2 + a3 + a4;

	if (pSum - rSum > 2)
		return false;

	// Figure out which line is being intersected with
	vec::Vector2 p1, p2;

	float minArea = minVal(a1, a2, a3, a4);
	if (minArea == a1)
	{
		p1 = tl;
		p2 = bl;
	}
	else if (minArea == a2)
	{
		p1 = bl;
		p2 = br;
	}
	else if (minArea == a3)
	{
		p1 = br;
		p2 = tr;
	}
	else if (minArea == a4)
	{
		p1 = tr;
		p2 = tl;
	}

	// Calculate the normal of this line
	normal = (p1 - p2).rotate(PI / 2).setMag(1);
	normal *= -1;

	// Make sure the normal is pointing outwards
	vec::Vector2 difC = point - this->getPos();
	if (normal.angleBetween(difC) > 90)
		normal *= -1;
	
	return true;
}


//          GETTERS & SETTERS          //
void Rect::setPos(const vec::Vector2& _pos)
{
	vec::Vector2 diff = _pos - center;

	center = _pos;
	tl += diff;
	tr += diff;
	bl += diff;
	br += diff;
}

sf::FloatRect Rect::getAABB() const
{
	sf::FloatRect aabb;

	aabb.left = minVal(tl.getX(), tr.getX(), bl.getX(), br.getX());
	aabb.top = minVal(tl.getY(), tr.getY(), bl.getY(), br.getY());

	aabb.width = maxVal(tl.getX(), tr.getX(), bl.getX(), br.getX()) - aabb.left;
	aabb.height = maxVal(tl.getY(), tr.getY(), bl.getY(), br.getY()) - aabb.top;

	return aabb;
}

float Rect::minVal(float a, float b, float c, float d) const
{
	float min = a;
	min = min < b ? min : b;
	min = min < c ? min : c;
	min = min < d ? min : d;

	return min;
}

float Rect::maxVal(float a, float b, float c, float d) const
{
	float max = a;
	max = max > b ? max : b;
	max = max > c ? max : c;
	max = max > d ? max : d;

	return max;
}

vec::Vector2 Rect::getPos() const
{
	return center;
}

float Rect::getRad() const
{
	return radius;
}


//          PRIVATE FUNCTIONS          //

void Rect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape center;
	center.setFillColor(sf::Color::Magenta);

	center.setOrigin(2, 2);
	center.setRadius(2);
	center.setPosition(getPos().getX(), getPos().getY());

	target.draw(center, states);

	sf::ConvexShape drawRect;

	drawRect.setPointCount(4);
	drawRect.setPoint(0, sf::Vector2f(tl.getX(), tl.getY()));
	drawRect.setPoint(1, sf::Vector2f(tr.getX(), tr.getY()));
	drawRect.setPoint(2, sf::Vector2f(br.getX(), br.getY()));
	drawRect.setPoint(3, sf::Vector2f(bl.getX(), bl.getY()));

	drawRect.setFillColor(sf::Color::Transparent);
	drawRect.setOutlineColor(sf::Color::Magenta);
	drawRect.setOutlineThickness(1);

	target.draw(drawRect, states);
}

// Re-calculates the radius and center of mass
void Rect::calcRad()
{
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


// Calculates the area of a triangle
float Rect::areaOf(const vec::Vector2& p1, const vec::Vector2& p2, const vec::Vector2& p3) const
{
	float a = abs(p1.getX() * (p2.getY() - p3.getY()) +
		p2.getX() * (p3.getY() - p1.getY()) +
		p3.getX() * (p1.getY() - p2.getY()));
	a /= 2;

	return a;
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
	_type = CIRC;
}

Circ::~Circ() {}


bool Circ::collide(const Shape* shape, vec::Vector2& normal) const
{
	// Check for a null-pointer
	if (shape == NULL)
		return false;

	bool isColliding = false;

	// If rect-circ collision
	if (shape->getTypeEnum() == RECT)
	{
		const Rect* r = dynamic_cast<const Rect*>(shape);
		// Check for a null-cast
		if (r == NULL)
			return false;

		isColliding = collideRC(*r, *this, normal);
	}
	// If circ-circ collision
	else if (shape->getTypeEnum() == CIRC)
	{
		const Circ* c = dynamic_cast<const Circ*>(shape);
		// Check for a null-cast
		if (c == NULL)
			return false;

		//I f the distance is less than the sum of the radii, colliding
		if (c->getPos().dist(this->getPos()) < (this->getRad() + c->getRad()))
		{
			isColliding = true;
			normal = (this->getPos() - c->getPos()).setMag(1);
		}
	}

	return isColliding;
}


void Circ::move(const vec::Vector2& moveAmount)
{
	pos += moveAmount;
}



//          GETTERS & SETTERS          //
void Circ::setPos(const vec::Vector2& _pos)
{
	pos = _pos;
}

vec::Vector2 Circ::getPos() const
{
	return pos;
}

float Circ::getRad() const
{
	return radius;
}

sf::FloatRect Circ::getAABB() const
{
	return sf::FloatRect(getPos().getX() - radius, getPos().getY() - radius,
		radius * 2, radius * 2);
}


//         PRIVATE FUNCTIONS          //
void Circ::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape drawCircle;
	drawCircle.setFillColor(sf::Color::Transparent);
	drawCircle.setOutlineThickness(1);
	drawCircle.setOutlineColor(sf::Color::Magenta);

	drawCircle.setOrigin(radius, radius);
	drawCircle.setRadius(getRad());
	drawCircle.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	
	target.draw(drawCircle, states);
}

/////////////////////////////////////////
//          GLOBAL FUNCTIONS           //
/////////////////////////////////////////

bool lineIntCirc(const vec::Vector2& p1, const vec::Vector2& p2, const Circ& c, vec::Vector2& normal)
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

	if (theta1 > PI / 2)
	{
		float d = x2.getMag();
		if (d < c.getRad())
			isInt = true;
	}
	else if (theta2 > PI / 2)
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

	// Generate normal if colliding
	if (isInt)
	{
		// Calculate the normal of this line
		normal = (p1 - p2).rotate(PI / 2).setMag(1);
	}

	return isInt;
}

bool collideRC(const Rect& r, const Circ& c, vec::Vector2& normal)
{
	// Check if they're near each other
	if (r.getPos().dist(c.getPos()) > r.getRad() + c.getRad())
		return false;

	bool colliding = false;

	// If they are, check all lines for intersection
	if (lineIntCirc(r.tl, r.tr, c, normal))
		colliding = true;
	if (lineIntCirc(r.tr, r.br, c, normal))
		colliding = true;
	if (lineIntCirc(r.br, r.bl, c, normal))
		colliding = true;
	if (lineIntCirc(r.bl, r.tl, c, normal))
		colliding = true;

	if (r.pointInRect(c.getPos(), normal))
		colliding = true;

	return colliding;
}