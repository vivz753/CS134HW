#pragma once
#include "ofMain.h"
#include "Sprite.h"

typedef enum { EMITTERA, EMITTERB, EMITTERC, GUN } EmitterType;

class Emitter : public Sprite {
public:
	Emitter(EmitterType);
	EmitterType emitterType;
	void init();
	void draw();

	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setImage(ofImage);
	void setRate(float);
	void shoot();
	void update();
	void translate(int, int);
	void translate(ofVec3f);
	float maxDistPerFrame();
	bool collided(ofVec3f, float);

	bool shooting;
	SpriteSystem sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool haveChildImage;
	bool  haveImage;
	float width, height;
	
};