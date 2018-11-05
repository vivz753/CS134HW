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
	void mousePressed(int, int, int);
	void mouseDragged(int, int, int);
	void mouseReleased(int, int, int);

	float playerScore;
	
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;

	Emitter gunEmitter;
	Emitter emitterA;
	Emitter emitterB;
	Emitter emitterC;
	Emitter emitterB2;

	bool beatLevelOne;

	ParticleEmitter * pe;

	vector<Emitter> emitters;
	Sprite a = Sprite(A);
	Sprite b = Sprite(B);
	Sprite c = Sprite(C);
};