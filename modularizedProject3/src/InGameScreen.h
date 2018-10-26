#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"

typedef enum { Level1, Level2, Level3 } LevelName;

class InGameScreen : public Screen {
public:
	InGameScreen(LevelName);
	LevelName levelName;
	void init();
	void draw();
	void update();
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;
};