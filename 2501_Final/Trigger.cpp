
#include "Trigger.h"

Trigger::Trigger(void (*func)()) {
	react = func;
}

void Trigger::onCollide(const Collideable& other) {
	react();
}