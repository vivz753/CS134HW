#include "Sprite.h"

Sprite::Sprite(SpriteType sType) {
	spriteType = sType;

	//hardcoded
	trans = ofVec2f(250, 250);
	width = 50;
	height = 50;
};

void Sprite::draw() {
	switch (spriteType) {
	case A:
		//set appearance
		image.load("cookie.png");

		break;
	case B:
		image.load("pokeball.png");
		break;
	case C:
		image.load("dragonball.png");
		break;
	case BULLET:
		image.load("arrow.png");
		break;
	}
	
	image.draw(trans, width, height);
};

void Sprite::setPosition(ofVec3f p) {
	trans = p;
};

float Sprite::age() {
	return ofGetElapsedTimeMillis() - birthtime;
};

void Sprite::setImage(ofImage i) {
	image = i;
};