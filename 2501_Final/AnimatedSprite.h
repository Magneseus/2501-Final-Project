#pragma once

#include "SFML\Graphics.hpp"

class AnimatedSprite : public sf::Sprite {
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool create(std::vector<sf::Texture*> inFrames, int inFrameRate);
	void update();

	const sf::Texture* getTexture();	// overriding Sprite method

private:
	std::vector<sf::Texture*> frames;

	int frameRate;
	int frameIndex;
	float elapsedTime;
	const int maxFrameSkip = 3;

	sf::Clock timer;
};