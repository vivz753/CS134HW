#include "Sprite.h"



Sprite::Sprite()
{
	trans = ofVec2f(250, 0);
	width = 50;
	height = 50;
	haveImage = false;
}


void Sprite::draw() {
	//draw a blue box by default if no image is set
	if (!haveImage) {
		ofSetColor(ofColor::blue);
		ofDrawRectangle(trans, width, height);
	}
	else {
		image.draw(trans, width, height);
	}
};


float Sprite::age() {
	return ofGetElapsedTimeMillis() - birthtime;
};

void Sprite::setImage(ofImage i) {
	image = i;
	haveImage = true;
};
