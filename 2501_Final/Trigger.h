#pragma once

#include "GameObject.h"

/*					    	TRIGGER
	A concrete class that handles in game (invisible) triggers. 

	- react is a function, called when the trigger is collided with
*/

class Trigger : public Collideable {
public:
	Trigger(void (*)());
	~Trigger();

	virtual void onCollide(const Collideable& other);

private:
	void(*react)();
};