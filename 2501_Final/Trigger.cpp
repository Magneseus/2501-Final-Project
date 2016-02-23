
#include "Trigger.h"

Trigger::Trigger(void (*func)()) {
	react = func;
}

Trigger::~Trigger() {

}

void Trigger::onCollide(const Collideable& other) {
	react();
}