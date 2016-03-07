
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() {
	elapsedTime = 0;
	frameIndex = 0;
	timer.restart();
}

AnimatedSprite::~AnimatedSprite() {}

bool AnimatedSprite::create(std::vector<sf::Texture*> inFrames, int inFrameRate) {
	frames = inFrames;
	frameRate = inFrameRate;

	return true;
}

void AnimatedSprite::update() {
	elapsedTime += timer.restart().asSeconds();	// add passed time

	float timePerFrame = 1 / frameRate;	// inverse of fps - seconds per frame

	int numFrames = elapsedTime / timePerFrame;		// number of frames that should pass

	// if we should pass more frames than we're allowed, don't
	if (numFrames > maxFrameSkip) numFrames = maxFrameSkip;

	if (numFrames > 0) elapsedTime = 0;

	frameIndex = (frameIndex + numFrames) % frames.size();
}

const sf::Texture* AnimatedSprite::getTexture() {
	return frames[frameIndex];
}

