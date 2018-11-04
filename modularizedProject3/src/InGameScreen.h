#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"
#include "Sprite.h"

typedef enum { Level1, Level2, Level3 } LevelType;

class InGameScreen : public Screen {
public:
	InGameScreen();
	//InGameScreen(LevelName)
	LevelType levelType;
	void setLevel(LevelType);
	void setLevel(int);
	void init();
	void terminate();
	void draw();
	void update();

	void checkCollisions();

	void keyPressed(int);
	void keyReleased(int);
	void mouseMoved(int, int);

	float playerScore;
	
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;

	Emitter gunEmitter;
	Emitter emitterA;
	Emitter emitterB;
	Emitter emitterC;

	ParticleEmitter * pe;

	vector<Emitter> emitters;
	Sprite a = Sprite(A);
	Sprite b = Sprite(B);
	Sprite c = Sprite(C);

	//create vector of emitters
	//hp
	//points
	//gun emitter (emitters can be 1, 2, 3 type; emitter 1 spits sprite a, emitter 2 spits sprite a & b, emitter 3 spits sprite a & b & c)
	//gun image
	//bullet image
};