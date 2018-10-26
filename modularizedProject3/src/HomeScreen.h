#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"

typedef enum { DEFAULT, SELECTLEVEL } MenuType;

class HomeScreen : public Screen {
public:
	HomeScreen();
	MenuType menuType;
	int transitionLevel;
	//LevelType transitionLevel;
	void init();
	void draw();
	void update();
	void keyPressed(int);
	void terminate();
	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;
};