#pragma once

#include "Screen.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ParticleEmitter.h"

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
	void terminate();

	void keyPressed(int);
	void keyReleased(int);
	void mouseMoved(int, int);

	ofImage background;
	ofSoundPlayer bgMusic;
	ofTrueTypeFont text;


	//test code
	RadialForce * radialForce = new RadialForce();

	//simulate exhaust of engine
	ParticleEmitter pe = ParticleEmitter();
};