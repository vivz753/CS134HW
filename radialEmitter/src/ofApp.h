#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Particle.h"
#include "ParticleEmitter.h"



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
		void loadVbo();

		ofEasyCam    cam;

	
	    // Emitter and some forces;
		//
		ParticleEmitter emitter;

		TurbulenceForce *turbForce;
		GravityForce *gravityForce;
		ImpulseRadialForce *radialForce;
		CyclicForce *cyclicForce;


		// some simple sliders to play with parameters
		//
		bool bHide;
		ofxFloatSlider gravity;
		ofxFloatSlider damping;
		ofxFloatSlider radius;
		ofxVec3Slider velocity;
		ofxIntSlider numParticles;
		ofxFloatSlider lifespan;
		ofxVec2Slider lifespanRange;
		ofxVec3Slider turbMin;
		ofxVec3Slider turbMax;
		ofxFloatSlider mass;
		ofxFloatSlider radialForceVal;
		ofxFloatSlider radialHight;
		ofxFloatSlider cyclicForceVal;
		ofxFloatSlider rate;
		ofxPanel gui;

		
		// textures
		//
		ofTexture  particleTex;

		// shaders
		//
		ofVbo vbo;
		ofShader shader;
};
