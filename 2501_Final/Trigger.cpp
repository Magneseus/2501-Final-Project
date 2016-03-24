
#include "Trigger.h"

Trigger::Trigger(std::function<void()> callback) {
	react = callback;
}

Trigger::~Trigger() {

}

void Trigger::onCollide(const Collidable& other) {
	react();
}