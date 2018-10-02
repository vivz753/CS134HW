#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Particle {
public: 
	Particle();
	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	float	damping;
	float   mass;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    integrate();
	void    draw();
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

		void launchParticle();

		ofEasyCam    cam;
		float framerate;

		// some simple sliders to play with parameters
		//
		bool bHide;
		ofxFloatSlider gravity;
		ofxFloatSlider damping;
		ofxFloatSlider radius;
		ofxVec3Slider velocity;
		ofxPanel gui;
		vector<Particle> particles;
		Particle display;
};
