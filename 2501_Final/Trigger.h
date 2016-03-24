#pragma once

#include "GameObject.h"

#include <functional>

/*					    	TRIGGER
	A concrete class that handles in game (invisible) triggers. 

	- react is a function, called when the trigger is collided with
*/

class Trigger : public Collidable {
public:
	Trigger(std::function<void()> callback);
	~Trigger();

	virtual void onCollide(const Collidable& other);

private:
	std::function<void()> react;
};