#pragma once
#include "ofMain.h"
#include "Sprite.h"



class Emitter : public BaseObject
{
public:
	//assets
	ofSoundPlayer shootSound;

	//constructor
	Emitter();
	void gunInit();
	void enemiesInit(float);

	//methods
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
	

	//attributes
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
	bool enemyEmitter;
	bool moving;
	ofVec3f movingVector;
	int hp;
	int score;
	bool dead;
};


