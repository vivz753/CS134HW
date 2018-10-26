#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"

typedef enum { Level1, Level2, Level3 } LevelType;

class InGameScreen : public Screen {
public:
	InGameScreen();
	//InGameScreen(LevelName)
	LevelType levelType;
	void setLevel(LevelType);
	void setLevel(int);
	void init();
	void draw();
	void update();
	void keyPressed(int);
	void terminate();
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;

	//create vector of emitters
	//hp
	//points
	//gun emitter (emitters can be 1, 2, 3 type; emitter 1 spits sprite a, emitter 2 spits sprite a & b, emitter 3 spits sprite a & b & c)
	//gun image
	//bullet image
};