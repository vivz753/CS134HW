#pragma once
#include "ofMain.h"
#include "Sprite.h"

typedef enum { EMITTERA, EMITTERB, EMITTERC, GUN } EmitterType;

class Emitter {
	ofVec3f trans;
	void setPosition(ofVec3f);
	float width, height;
	ofImage image;
	void setImage(ofImage);

	Emitter(EmitterType);
	EmitterType emitterType;
	void init();
	void draw();
	void start();
	void stop();
	void shoot();

	float lastSpawned;
	ofImage childImage;
	SpriteSystem *sys;
};