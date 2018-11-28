#include "Sprite.h"

Sprite::Sprite(SpriteType sType) {
	spriteType = sType;

	//hardcoded
	trans = ofVec2f(250, 250);
	velocity = ofVec3f(0,0,0);
	lifespan = 0;
	width = 50;
	height = 50;
	rectangle = ofRectangle(trans, width, height);
};

void Sprite::init() {
	//switch (spriteType) {
	//case A:
	//	//set appearance, velocity, lifepspan, width, height
	//	image.load("cookie.png");
	//	break;
	//case B:
	//	image.load("pokeball.png");
	//	break;
	//case C:
	//	image.load("dragonball.png");
	//	break;
	//case BULLET:
	//	image.load("arrow.png");
	//	break;
	//}

}

void Sprite::draw() {
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