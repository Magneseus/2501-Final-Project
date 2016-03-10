#pragma once

#include "Shape.h"
#include <vector>

class Collider : public sf::Drawable
{
public:
	Collider();
	Collider(const std::vector<Shape*>, const vec::Vector2&);
	~Collider();

	bool collide(Collider&) const;

	void move(const vec::Vector2&);
	void moveTo(const vec::Vector2&);
	void rotate(float);
	void rotateTo(float);

	void addShape(Shape*);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Shape*> hitbox;
	vec::Vector2 position;
	float angle;

};