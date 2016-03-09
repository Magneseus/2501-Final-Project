
#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite() {
	elapsedTime = 0;
	frameIndex = 0;
}

AnimatedSprite::~AnimatedSprite() {}

bool AnimatedSprite::create(std::vector<sf::Texture*> inFrames, int inFrameRate) {
	frames = inFrames;
	frameRate = inFrameRate;

	return true;
}

void AnimatedSprite::update() {

	elapsedTime += timer.restart().asSeconds();	// add passed time

	float timePerFrame = 1.0 / frameRate;	// inverse of fps - seconds per frame

	int numFrames = elapsedTime / timePerFrame;		// number of frames that should 

	// if we should pass more frames than we're allowed, don't
	if (numFrames > maxFrameSkip) numFrames = maxFrameSkip;

	if (numFrames > 0) elapsedTime = 0;

	frameIndex = (frameIndex + numFrames) % frames.size();
}

const sf::Texture* AnimatedSprite::getTexture() {
	return frames[frameIndex];
}

void AnimatedSprite::draw(sf::RenderWindow* w) {
	update();

	this->setTexture(*(getTexture()));
	w->draw(*this);
}
