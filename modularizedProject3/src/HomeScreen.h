#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"

class HomeScreen : public Screen {
public:
	HomeScreen();
	void init();
	void draw();
	void update();
	void keyPressed(int);
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;
};