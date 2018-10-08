//DESCRIPTION:
//Project 1 Part 2 submission by Vivian Leung for Prof. Kevin Smith's CS134 at SJSU 10/8/2018

//INSTRUCTIONS:
//Press spacebar to begin. Use mouse or WASD keys to move gun around. Press space or click to shoot bullets. Press q to quit.


#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void checkCollisions();
		void checkHealth();
		
		Sprite collider;
		Emitter gunEmitter;
		ofxFloatSlider firingRateSlider;
		ofxFloatSlider velocityXSlider;
		ofxFloatSlider velocityYSlider;
		ofxFloatSlider lifeSpanSlider;
		ofxVec3Slider velocitySlider;

		ofxPanel gui;
		bool pressingMouse;
		ofImage background;
		ofSoundPlayer bgMusic;
		ofTrueTypeFont text;

		ofImage gun;
		ofImage bullet;
		vector<Emitter *> enemies;
		bool keyIsDown[4];
		
};
