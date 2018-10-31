#pragma once
#include "ofMain.h"
#include "Sprite.h"

typedef enum { EMITTERA, EMITTERB, EMITTERC, GUN } EmitterType;

class Emitter {
public:
	ofVec3f trans;
	void setPosition(ofVec3f);
	float width, height;
	ofImage parentImage;
	ofImage childImage;
	float lastSpawned;
	bool emitting;

	//for gun emitters only
	bool moving;
	ofVec3f movingVector;

	Emitter();
	Emitter(EmitterType);
	EmitterType emitterType;
	void init();
	void draw();
	void shoot();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setrate(float);
	void update();

	void translate(int, int);
	void translate(ofVec3f);

	float maxdistperframe();
	bool collided(ofVec3f, float);

	bool shooting;
	SpriteSystem *sys;
	float rate;
	//bool started;
	float lifespan;
	ofVec3f velocity;

	
};