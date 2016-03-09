#pragma once

#include "SFML\Graphics.hpp"

/*					AnimatedSprite
	Created as a class to be used in place of Sprites,
	when the intention is to have it changing. Store 
	an instance of the class, and call draw(window) to
	draw it to the window, which updates the frame too.

	Has an internal clock that is used so it does not
	need to be updated in updatables.
*/

class AnimatedSprite : public sf::Sprite {
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool create(std::vector<sf::Texture*> inFrames, int inFrameRate);
	void update();

	const sf::Texture* getTexture();	// overriding Sprite method
	void draw(sf::RenderWindow*);

private:
	// change this to a single texture, draw from it
	std::vector<sf::Texture*> frames;

	// have multiple states

	int frameRate;
	int frameIndex;
	float elapsedTime;
	const int maxFrameSkip = 3;

	sf::Clock timer;
};