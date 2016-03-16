
#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(SpriteSheet* s, int _frameRate) {
	frameIndex = 0;
	stateIndex = 0;
	elapsedTime = 0;
	frameRate = _frameRate;
	sheet = s;
}

AnimatedSprite::~AnimatedSprite() {}

void AnimatedSprite::addState(std::vector<sf::String> newNames) {
	SpriteState newState;
	newState.start = fileNames.size();
	newState.numFrames = newNames.size();
	states.push_back(newState);

	// add names
	for (size_t i = 0; i < newNames.size(); i++) {
		fileNames.push_back(newNames[i]);
	}
}

void AnimatedSprite::changeState(int newState) {
	if (newState < 0 || newState >= states.size()) return;
	stateIndex = newState;
	frameIndex = 0;
	elapsedTime = 0;
}

void AnimatedSprite::update(const sf::Time& delta) {
	elapsedTime += delta.asSeconds();	// add passed time

	float timePerFrame = 1.0 / frameRate;	// inverse of fps - seconds per frame

	int numFrames = elapsedTime / timePerFrame;		// number of frames that should 

	// if we should pass more frames than we're allowed, don't
	if (numFrames > maxFrameSkip) numFrames = maxFrameSkip;

	if (numFrames > 0) elapsedTime = 0;

	SpriteState cur = states[stateIndex];

	frameIndex = (frameIndex + numFrames) % cur.numFrames;

	sprite.setTexture(*(sheet->getTex(fileNames[frameIndex+cur.start])));
	sprite.setOrigin(static_cast<sf::Vector2f>(sheet->getTexPivot(fileNames[frameIndex])));	// disgusting line of code
	sprite.setPosition(position.getSfVec());
	sprite.setRotation(rotation);
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}
