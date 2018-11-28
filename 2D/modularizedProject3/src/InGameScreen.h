#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"
#include "Sprite.h"

typedef enum { Level1, Level2, Level3, WIN, LOSE } LevelType;

class InGameScreen : public Screen {
public:

	bool firstInit = true;
	vector<float> scores;
	ofSoundPlayer winSound;
	ofSoundPlayer loseSound;
	ofSoundPlayer bgMusic;

	void addEnemies();
	bool addedEnemies;
	bool confirmedSwitch;
	float initTime;

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
	void removeDeadEmitters();

	void keyPressed(int);
	void keyReleased(int);
	void mouseMoved(int, int);
	void mousePressed(int, int, int);
	void mouseDragged(int, int, int);
	void mouseReleased(int, int, int);

	float playerScore;
	
	ofImage background;
	ofSoundPlayer igMusic;
	ofTrueTypeFont text;

	Emitter gunEmitter;
	Emitter catPumpkinBoss;
	Emitter emitterA;
	Emitter emitterA2;
	Emitter emitterB;
	Emitter emitterB2;
	Emitter emitterB3;
	Emitter emitterB4;

	bool beatLevelOne;
	bool beatLevelTwo;
	bool allDead;

	ParticleEmitter * pe;

	vector<Emitter> emitters;
	Sprite a = Sprite(A);
	Sprite b = Sprite(B);
	Sprite c = Sprite(C);
};