#include "Collider.h"

Collider::Collider()
	: position(vec::Vector2(0,0)),
	angle(0)
{

}

Collider::Collider(const std::vector<Shape*> _shapes, const vec::Vector2& _pos)
	: position(_pos),
	hitbox(_shapes),
	angle(0)
{
	// Moves all shapes according to the center to align properly
	for (int i = 0; i < hitbox.size(); i++)
	{
		hitbox.at(i)->move(position);
	}
}

Collider::~Collider()
{
	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

	hitbox.clear();
}



////////////////////////////////
//      PUBLIC FUNCTIONS      //
////////////////////////////////

/*
	Checks for a collision with another hitbox.

	O(n^2) worst case
*/
bool Collider::collide(Collider& other) const
{
	return collide(other, vec::Vector2());
}

/*
	Checks for a collision with another hitbox and sets the normal vector.

	O(n^2) worst case
*/
bool Collider::collide(Collider& other, vec::Vector2& normal) const
{
	// Loop through all shapes in each hitbox
	for (auto it1 = hitbox.begin(); it1 != hitbox.end(); ++it1)
	{
		for (auto it2 = other.hitbox.begin(); it2 != other.hitbox.end(); ++it2)
		{
			if ((*it1)->collide(*it2, normal))
			{
				return true;
			}
		}
	}

	return false;
}

/*
	This function generates and returns the AABB of
	the hitbox of this collider.
*/
sf::FloatRect Collider::getAABB() const
{
	sf::FloatRect aabb;

	if (hitbox.size() > 0)
	{
		aabb = hitbox.at(0)->getAABB();
	}

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		sf::FloatRect aabb2 = (*it)->getAABB();

		if (aabb2.left < aabb.left) aabb.left = aabb2.left;
		if (aabb2.top < aabb.top) aabb.top = aabb2.top;

		float right = aabb.left + aabb.width;
		float right2 = aabb2.left + aabb2.width;
		if (right2 > right) aabb.width = right2 - aabb.left;

		float bottom = aabb.top + aabb.height;
		float bottom2 = aabb2.top + aabb2.height;
		if (bottom2 > bottom) aabb.height = bottom2 - aabb.top;
	}

	return aabb;
}

void Collider::addShape(Shape* shp)
{
	// Check for RECT shapes
	if (shp->getTypeEnum() == RECT)
	{
		Rect* r = dynamic_cast<Rect*>(shp);
		r->rotate(angle);
	}

	//Get center of each shape
	vec::Vector2 tpos = shp->getPos();

	//Translate by center
	tpos -= position;
	//Rotate
	tpos.rotate(angle);
	//Translate back
	tpos += position;

	//Re-set the position
	shp->setPos(tpos);


	// Add it to the list
	hitbox.push_back(shp);
}

/*
	Moves all shapes in the hitbox by _vec.
*/
void Collider::move(const vec::Vector2& _vec)
{
	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		(*it)->move(_vec);
	}
	position += _vec;
}

/*
	Moves all shapes in the hitbox to _vec.
*/
void Collider::moveTo(const vec::Vector2& _vec)
{
	// Finds the vector from the current center to the new position
	vec::Vector2 d = _vec - position;

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		(*it)->move(d);
	}
	position = _vec;
}

/*
	Rotates all shapes about the center of the hitbox by _ang radians.
*/
void Collider::rotate(float _ang)
{
	// Bind angle to within 0-2PI bounds
	angle += _ang;
	if (angle > 2.0 * PI)
		angle = std::fmod(angle, (2.0 * PI));
	else if (angle < 0.0)
		angle = (2.0 * PI) - std::fmod(std::abs(angle), (2.0 * PI));

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		// Check for RECT shapes
		if ((*it)->getTypeEnum() == RECT)
		{
			Rect* r = dynamic_cast<Rect*>((*it));
			r->rotateTo(angle);
		}

		//Get center of each shape
		vec::Vector2 tpos = (*it)->getPos();

		//Translate by center
		tpos -= position;
		//Rotate
		tpos.rotate(_ang);
		//Translate back
		tpos += position;

		//Re-set the position
		(*it)->setPos(tpos);
	}
}

/*
	Rotates all shapes about the center of the hitbox to _ang radians.
*/
void Collider::rotateTo(float _ang)
{
	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		// Check for RECT shapes
		if ((*it)->getTypeEnum() == RECT)
		{
			Rect* r = dynamic_cast<Rect*>((*it));
			r->rotateTo(_ang);
		}

		//Get center of each shape
		vec::Vector2 tpos = (*it)->getPos();

		//Translate by center
		tpos -= position;
		//Rotate
		tpos.rotate(-angle);
		tpos.rotate(_ang);
		//Translate back
		tpos += position;

		//Re-set the position
		(*it)->setPos(tpos);
	}

	angle = _ang;
}



/////////////////////////////////
//      PRIVATE FUNCTIONS      //
/////////////////////////////////

void Collider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape center;
	center.setFillColor(sf::Color::Magenta);
	
	center.setOrigin(4, 4);
	center.setRadius(4);
	center.setPosition(position.getX(), position.getY());

	target.draw(center, states);

	for (auto it = hitbox.begin(); it != hitbox.end(); ++it)
	{
		target.draw(**it, states);
	}

	sf::RectangleShape aabbShape;
	aabbShape.setFillColor(sf::Color::Transparent);
	aabbShape.setOutlineThickness(1);
	aabbShape.setOutlineColor(sf::Color::Red);

	sf::FloatRect aabb = getAABB();
	aabbShape.setPosition(aabb.left, aabb.top);
	aabbShape.setSize(sf::Vector2f(aabb.width, aabb.height));
	target.draw(aabbShape, states);
}