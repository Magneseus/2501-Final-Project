#pragma once

#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "SpriteSheet.h"

/*					AnimatedSprite
	Created as a class to be used in place of Sprites,
	when the intention is to have it changing.
*/

struct SpriteState {
	int start;
	int numFrames;
};

class AnimatedSprite : public Drawable, public Updatable {
public:
	AnimatedSprite(SpriteSheet* s, int _frameRate);
	~AnimatedSprite();

	void addState(std::vector<sf::String> newNames);

	void changeState(int newState);

	void update(const sf::Time&);	// from updatable

private:
	std::vector<sf::String> fileNames;
	std::vector<SpriteState> states;

	SpriteSheet* sheet;

	int frameRate;
	int frameIndex;	// in the current sequence
	int stateIndex;
	float elapsedTime;
	const int maxFrameSkip = 3;

	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	// from Drawable
};