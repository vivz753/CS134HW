#pragma once
#include "ofMain.h"
#include "Sprite.h"



class Emitter : public BaseObject
{
public:
	ofSoundPlayer shootSound;
	Emitter(SpriteSystem s);
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
	bool shooting;
	SpriteSystem sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	float width, height;
	
};


