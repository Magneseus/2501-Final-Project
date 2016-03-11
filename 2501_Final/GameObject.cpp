#include "GameObject.h"

// TODO: Fix this stupid way of doing things
// (Probably make the GameObject file into an actual proper implementation)

std::vector<GameObject*> GameObject::staticGameObjects;
std::vector<GameObject*> GameObject::staticGameObjectsDel;
std::vector<GameObject*> GameObject::staticGameObjectsRem;

// Some more sp00ky global/static stuff
sf::Vector2i Global::mouseWindowCoords;

void Entity::update(const sf::Time& delta) {
	// TODO: Don't have it always look at mouse
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
	//vel *= .999999; DRAG?

	if (vel.getMag() > topSpeed) vel.setMag(topSpeed);

	vec::Vector2 strafeAccel(toRadians(bearing + 90));
	strafeAccel.setMag(rotateSpeed * strafe * delta.asSeconds());
	vel += strafeAccel;

	// Calculate position
	pos += vel * delta.asSeconds();
}