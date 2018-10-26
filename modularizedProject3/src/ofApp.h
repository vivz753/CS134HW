#pragma once

#include "ofMain.h"
#include "HomeScreen.h"
#include "InGameScreen.h"
#include "Screen.h"
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
			screen->init();
		};

		Screen * screen;
		HomeScreen * home = new HomeScreen();
		InGameScreen * inGame = new InGameScreen();
};
