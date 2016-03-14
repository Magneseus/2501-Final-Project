#include "GameObject.h"

// TODO: Fix this stupid way of doing things
// (Probably make the GameObject file into an actual proper implementation)

std::vector<GameObject*> GameObject::staticGameObjects;
std::vector<GameObject*> GameObject::staticGameObjectsDel;
std::vector<GameObject*> GameObject::staticGameObjectsRem;

// Some more sp00ky global/static stuff
sf::Vector2i Global::mouseWindowCoords;
sf::Font Global::niceFont;

void Entity::update(const sf::Time& delta) {
	// TODO: Don't have it always look at mouse
	// TODO: Clean this up to optimize, maybe a "turnable" boolean?
	vec::Vector2 mousePos = vec::Vector2(Global::mouseWindowCoords.x, Global::mouseWindowCoords.y);
	vec::Vector2 mDif = mousePos - vec::Vector2(400, 400);

	// Get the current turning direction
	vec::Vector2 turnVec(toRadians(bearing));

	// Set the turning direction
	double angDif = toDegrees(mDif.angleBetween(turnVec));
	angDif *= mDif.cross(turnVec) < 0 ? -1 : 1;

	if (angDif < 1 && angDif > -1)
		turning = STILL;
	else if (angDif < -1)
		turning = CLWISE;
	else
		turning = COCLWISE;

	bearing += delta.asSeconds() * rotateSpeed * turning;

	// Bind bearing
	if (bearing > 360)
		bearing = std::fmod(bearing, 360.0f);
	else if (bearing < 0)
		bearing = 360.0f - std::fmod(std::abs(bearing), 360.0f);

	// Calculate acceleration
	vec::Vector2 accel(toRadians(bearing));
	accel.setMag(accelRate * motion * delta.asSeconds());
	vel += accel;

	// Strafe acceleration
	vec::Vector2 strafeAccel(toRadians(bearing + 90));
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
	pos += vel * delta.asSeconds();
}