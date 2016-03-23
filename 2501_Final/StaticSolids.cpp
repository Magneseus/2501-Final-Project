#include "StaticSolids.h"

Wall::Wall(vec::Vector2 _topleft, vec::Vector2 _bottomright, sf::Texture* _tex)
{
	wallSprite.setTexture(*_tex);

	Rect* r = new Rect(_topleft, _bottomright);
	col.addShape(r);

	setPosition(_topleft + ((_bottomright - _topleft)/2.0f));
	
	setSolid(true);
	setStatic(true);
}

Wall::~Wall() {}

void Wall::onCollide(Collidable& other)
{

}


void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(wallSprite, states);
	target.draw(col, states);
}