#pragma once

#include "ofMain.h"

class RectObj {
	public:
		ofVec2f pos;
		float w = 100;
		float h = 100;
		int previousX;
		int previousY;
		bool clickedInside;
		bool switchColors = false;

		void draw() {
			if (switchColors) ofSetColor(ofColor::green);
			else ofSetColor(ofColor::red);
			ofDrawRectangle(pos, 100, 100);
		}

		void clicked(int x, int y) {
			clickedInside = ((x > pos.x && x < pos.x + w) && (y > pos.y && pos.y + h));
			previousX = x;
			previousY = y;
			switchColors = !switchColors;
		}

		void released(){
			switchColors = !switchColors;
		}

		//bool inside(int x, int  y) {
		//	clickedInside = ((x > pos.x && x < pos.x + w) && (y > pos.y && pos.y + h));
		//	previousX = x;
		//	previousY = y;
		//	return clickedInside;
		//}

		void translate(int x, int y) {
			int diffX = x - previousX;
			int diffY = y - previousY;
			pos.x += diffX;
			pos.y += diffY;
			previousX = x;
			previousY = y;
		}

};
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
		
		RectObj rect;
};
