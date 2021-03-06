#include "GameObject.h"

// TODO: Fix this stupid way of doing things
// (Probably make the GameObject file into an actual proper implementation)

std::vector<GameObject*> GameObject::staticGameObjects;
std::vector<GameObject*> GameObject::staticGameObjectsDel;
std::vector<GameObject*> GameObject::staticGameObjectsRem;

// Some more sp00ky global/static stuff
sf::Vector2i Global::mouseWindowCoords;
sf::Vector2f Global::mouseWorldCoords;
sf::Vector2i Global::middleWindowCoords;
sf::Font Global::niceFont;
Entity* Global::player = NULL;

vec::Vector2 Global::objective = NULL;

int Global::getState() { return game_state; }
void Global::setState(int in) {	game_state = in; }

int Global::game_state = -1;

bool Global::GAMEOVER = false;

bool Global::DEBUG = true;
bool Global::INFOCUS = true;

float Global::ZOOM = 1.0f;

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

void Entity::takeDamage(float amount) {
	healthBarTimer.restart();

	curHealth = std::fmax(curHealth - amount, 0);
	if (curHealth <= 0) {
		onDeath();
	}
}

void Entity::drawHealthBar(sf::RenderTarget& w, sf::RenderStates s) const {
	if (curHealth != maxHealth && healthBarTimer.getElapsedTime().asSeconds() < 5) {
		sf::RectangleShape barOut;
		barOut.setSize(sf::Vector2f(50, 5));
		barOut.setPosition(position.getX() - barOut.getSize().x / 2, position.getY() - 30);
		barOut.setOutlineColor(sf::Color::Black);
		barOut.setOutlineThickness(2);
		sf::Color grey = sf::Color::Black;
		grey.r += 100;
		grey.g += 100;
		grey.b += 100;
		barOut.setFillColor(grey);

		sf::RectangleShape barIn(barOut);
		barIn.setSize(sf::Vector2f(barOut.getSize().x * (curHealth / maxHealth), barOut.getSize().y));
		barIn.setFillColor(sf::Color::Red);
		barIn.setOutlineThickness(0);

		w.draw(barOut, s);
		w.draw(barIn, s);
	}
}