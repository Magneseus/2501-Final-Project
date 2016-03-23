#include "GameObject.h"

// TODO: Fix this stupid way of doing things
// (Probably make the GameObject file into an actual proper implementation)

std::vector<GameObject*> GameObject::staticGameObjects;
std::vector<GameObject*> GameObject::staticGameObjectsDel;
std::vector<GameObject*> GameObject::staticGameObjectsRem;

// Some more sp00ky global/static stuff
sf::Vector2i Global::mouseWindowCoords;
sf::Vector2i Global::middleWindowCoords;
sf::Font Global::niceFont;
bool Global::DEBUG = true;

SpriteSheet* Global::globalSpriteSheet;

void Entity::debugDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (Global::DEBUG)
	{
		// Draw collision box
		target.draw(col, states);
	}
}

void Entity::update(const sf::Time& delta) {
	// TODO: Don't have it always look at mouse
	// TODO: Clean this up to optimize, maybe a "turnable" boolean?
	//vec::Vector2 mousePos = vec::Vector2(Global::mouseWindowCoords.x, Global::mouseWindowCoords.y);
	vec::Vector2 mDif = target - position;//vec::Vector2(400, 400);

	// Get the current turning direction
	vec::Vector2 turnVec(toRadians(rotation));

	// Set the turning direction
	double angDif = toDegrees(mDif.angleBetween(turnVec));
	angDif *= mDif.cross(turnVec) < 0 ? -1 : 1;

	if (angDif < 1 && angDif > -1)
		turning = STILL;
	else if (angDif < -1)
		turning = CLWISE;
	else
		turning = COCLWISE;

	rotation += delta.asSeconds() * rotateSpeed * turning;

	// Bind rotation
	if (rotation > 360)
		rotation = std::fmod(rotation, 360.0f);
	else if (rotation < 0)
		rotation = 360.0f - std::fmod(std::abs(rotation), 360.0f);

	// Calculate acceleration
	vec::Vector2 accel(toRadians(rotation));
	accel.setMag(accelRate * motion * delta.asSeconds());
	vel += accel;

	// Strafe acceleration
	vec::Vector2 strafeAccel(toRadians(rotation + 90));
	strafeAccel.setMag(accelRate * strafe * delta.asSeconds());
	vel += strafeAccel;
	
	// simulate drag, lose dragValue% speed/s if not thrusting
	// x2 dragValue% if "brakes" are on, stop earlier as well
	// brakes on overrules thrusting
	if (brakesOn || (motion == STILL && strafe == STILL)) {	
		vel *= std::fmin(1, 1 - (((brakesOn*3)+1) * dragValue * delta.asSeconds()));

		if (vel.getMag() < 25*((brakesOn*2)+1)) vel.setMag(0);
	}

	if (vel.getMag() > topSpeed) vel.setMag(topSpeed);

	// Calculate position
	position += vel * delta.asSeconds();
}

void Entity::takeDamage(float amount, Entity* source) {
	std::cout << getTag().toAnsiString() << " HP[" << curHealth << "/" << maxHealth <<
		"] is taking " << amount << " damage from " << 
		source->getTag().toAnsiString() << "." << std::endl;

	curHealth -= amount;
	if (curHealth <= 0) {
		std::cout << source->getTag().toAnsiString() << " destroyed " <<
			this->getTag().toAnsiString() << "." << std::endl;
		onDeath(source);
	}
}