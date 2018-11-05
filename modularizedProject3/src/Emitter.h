#pragma once
#include "ofMain.h"
#include "Sprite.h"
class SpriteSystem;

typedef enum { EMITTERA, EMITTERB, EMITTERC, GUN } EmitterType;

class Emitter {
public:
	ofVec3f trans;
	void setPosition(ofVec3f);
	float width, height;
	ofImage parentImage;
	ofImage childImage;
	float childWidth, childHeight;
	float lastSpawned;
	bool emitting;
	float hp;
	float totalHp;

	//for gun emitters only
	bool moving;
	ofVec3f movingVector;
	
	Sprite * setSpriteSettings(Sprite *);

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
	void checkCollision(SpriteSystem *);
	void checkCollision(Emitter);

	void translate(int, int);
	void translate(ofVec3f);

	bool shooting;
	SpriteSystem * sys;
	float rate;
	//bool started;
	float lifespan;
	ofVec3f velocity;

	ofRectangle rectangle;
	ofRectangle hpBar;
	
};