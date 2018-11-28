//Written by (me) Vivian Leung for Kevin Smith's CS134 class at SJSU
//ParticleEmitter/System/Particle & Emitter/SpriteSystem/Sprite classes by Kevin Smith w/ additional edits by me
//Finished on 11/5/2018 at 4:38 AM

#pragma once

#include "ofMain.h"
#include "HomeScreen.h"
#include "InGameScreen.h"
#include "Screen.h"
#include "Sprite.h"

#include "ofxGui.h"

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

		void setScreen(Screen * s) {
			if (screen != NULL) {
				screen->terminate();
			}
			screen = s;
			//screen->init();
		};

		void setLevel(int i) {
			switch (i) {
			case 1:
				inGame->setLevel(Level1);
				break;
			case 2:
				inGame->setLevel(Level2);
				break;
			case 3:
				inGame->setLevel(Level3);
				break;
			}
		}

		Screen * screen;
		HomeScreen * home = new HomeScreen();
		InGameScreen * inGame = new InGameScreen();

		
};
