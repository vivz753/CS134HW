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
		ofSetColor(ofColor::blue);

		//setImage(imageA)
		break;
	case B:
		ofSetColor(ofColor::red);
		//setImage(imageB)
		break;
	case C:
		ofSetColor(ofColor::white);
		//setImage(imageC)
		break;
	}

	ofDrawRectangle(trans, width, height);

	//image.draw(trans, width, height);
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