#include "Player.h"

Player::Player()
{
	
	spawn();

	enemy = NULL;

	playerTexture = Global::globalSpriteSheet->getTex("player.png");
	player.setTexture(*playerTexture);

	sf::Vector2i originV = Global::globalSpriteSheet->getTexPivot("player.png");
	player.setOrigin(originV.x, originV.y);
	
	player.setOrigin(25, 25);

	// Add a collison box for player
	//Rect* r = new Rect(vec::Vector2(-20, -20), vec::Vector2(20, 20));
	//col.addShape(r);
	Circ* c = new Circ(vec::Vector2(0, 0), 20);
	col.addShape(c);
	setSolid(true);

	// Set collision box tag
	setTag(sf::String("Player"));
}

Player::~Player()
{

}

void Player::update(const sf::Time& delta) {
	if (!Global::SPAWNING) {
		motion = STILL;
		turning = STILL;
		strafe = STILL;

		if (vehicle == NULL) {
			vel.setX(0);
			vel.setY(0);
		}
		else {
			vehicle->ship->changeState(0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (vehicle == NULL) {
				vel.setY(-topSpeed);
			}
			else {
				motion = FORWARD;
				vehicle->ship->changeState(1);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (vehicle == NULL) {
				vel.setY(topSpeed);
			}
			else {
				motion = REVERSE;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (vehicle == NULL) {
				vel.setX(topSpeed);
			}
			else {
				strafe = RIGHT;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (vehicle == NULL) {
				vel.setX(-topSpeed);
			}
			else {
				strafe = LEFT;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			brakesOn = true;
		}
		else {
			brakesOn = false;
		}

		if (vehicle && inputs.F) {
			inputs.F = false;
			exitVehicle();
		}

		target = vec::Vector2(Global::mouseWindowCoords.x - Global::middleWindowCoords.x + position.getX(),
			Global::mouseWindowCoords.y - Global::middleWindowCoords.y + position.getY());

		Entity::update(delta);

		player.setPosition(position.getX(), position.getY());

		if (vehicle != NULL) {
			vehicle->setPosition(position);
			vehicle->setRotation(rotation);
			vehicle->update(delta);
		}

		player.setRotation(rotation);

		// Set the textures
		if (motion == FORWARD) {
			//shipTexture = shipThrusting;
		}
		else {
			//shipTexture = shipStill;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (vehicle == NULL) {
				// on foot shoot
				currentWeapon->shoot(toRadians(rotation), position, this);
			}
			else {
				// in ship shoot
				currentLoadout->primary->shoot(toRadians(rotation), position, this);
			}
		}

		if (vehicle == NULL) {
			if (inputs.RClick) {
				switchWeapons();
			}
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				currentLoadout->secondary->shoot(toRadians(rotation), position, this);
			}
		}
	}
}

void Player::enterVehicle(Vehicle* v) {
	if (v != NULL) {
		remObjectStatic(v);
	}
	else { return; }	// if it's not a vehicle, don't try to use it

	vehicle = v;

	rotation = v->ship->getRotation();
	position = v->getPosition();

	accelRate = v->getAcceleration();
	topSpeed = v->getTopSpeed();
	rotateSpeed = v->getRotationSpeed();
	dragValue = v->getDragValue();

	switchLoadouts(v->weapons);

	// Store the old collider
	onFootCollider = col;

	// Get the new vehicle collider
	col = v->col;
	setTag(sf::String("Vehicle"));
}

void Player::exitVehicle() {
	if (vel.getMag() < 50) {

		// Update the vehicle's collider
		vehicle->col = this->col;

		// Reset our own collider
		col = onFootCollider;
		col.moveTo(this->getPosition());
		setTag(sf::String("Player"));

		addObjectStatic(vehicle);

		vehicle = NULL;
		vel.setX(0);
		vel.setY(0);

		accelRate = onFootAccel;
		topSpeed = onFootTopSpeed;
		rotateSpeed = onFootRotateSpeed;
		dragValue = 0;

		switchLoadouts(onFootLoadout);
	}
}

void Player::switchLoadouts(Loadout* newest) {
	currentLoadout = newest;
	currentWeapon = currentLoadout->primary;
}

void Player::switchWeapons() {
	if (currentWeapon == currentLoadout->primary) {
		currentWeapon = currentLoadout->secondary;
	} else {
		currentWeapon = currentLoadout->primary;
	}
}

void Player::spawn() {
	// deal with reseting player here
	// called at the beginning of game/round?

	vel = vec::Vector2(0, 0);
	position = vec::Vector2(0, 0);
	rotation = 0;

	accelRate = onFootAccel;
	topSpeed = onFootTopSpeed;
	rotateSpeed = onFootRotateSpeed;

	Global::SPAWNING = true;
}

void Player::getLoadoutOne() {
	// med
	onFootLoadout = new Loadout();
	onFootLoadout->primary = new Weapon(1, 10, 250);
	onFootLoadout->secondary = new Weapon(2, 5, 350);

	Global::FINISHEDSPAWN = true;

	switchLoadouts(onFootLoadout);
}

void Player::getLoadoutTwo() {
	// light
	onFootLoadout = new Loadout();
	onFootLoadout->primary = new Weapon(5, 5, 350);
	onFootLoadout->secondary = new Weapon(2, 15, 100);

	Global::FINISHEDSPAWN = true;

	switchLoadouts(onFootLoadout);
}

void Player::getLoadoutThree() {
	// heavy
	onFootLoadout = new Loadout();
	onFootLoadout->primary = new Weapon(1, 25, 150);
	onFootLoadout->secondary = new Weapon(0.5, 20, 500);

	Global::FINISHEDSPAWN = true;

	switchLoadouts(onFootLoadout);
}

void Player::onDeath(Entity* killer) {
	std::cout << "Player died from " << killer->getTag().toAnsiString() << "." << std::endl;
	exitVehicle();
	spawn();
}

void Player::onCollide(Collidable& other)
{
	//std::cout << "COLLIDE!: " << other.getTag().toAnsiString() << std::endl;
	if (other.getTag() == "Vehicle" && vehicle == NULL && inputs.F)
	{
		inputs.F = false;
		enterVehicle(dynamic_cast<Vehicle*>(&other));
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	if (vehicle != NULL) {
		target.draw(*vehicle, states);
	} else {
		target.draw(player, states);
	}


	drawHealthBar(target, states);

}