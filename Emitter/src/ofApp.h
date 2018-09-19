#pragma once

#include "ofMain.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject() {
		trans = ofVec2f(0,0);
		scale = ofVec2f(1);
		rot = 0;
	};
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f p) { 
		trans = p; }
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	Sprite() {
		//speed = theSpeed;
		//birthtime = ofGetElapsedTimeMillis(); 
		//lifespan = theLifespan;
		//ofVec2f pos;
		//haveImage = false;
		//width = theWidth;
		//height = theHeight;
	};
	void draw()	{
			ofVec2f pos;
			ofSetColor(ofColor::black);
			ofDrawRectangle(pos, 50, 50);
		};
	float age() {
	//currentTime  - birthtime
	};
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite) {
		sprites.push_back(Sprite());
		cout << "adding" << endl;
		//adds sprites to the vector array
	};
	void remove(int) {
		//removes sprite at index[int]
	}	;
	void update() {
		//cout << "updating" << endl;
		//keeps track of age of sprites
	};
	void draw() {
		//vector<Sprite> s::iterator;
		//for (int i = 0; i < &sprites.size(); i++) {
			//sprites[i].draw();
		//}
		//cout << sprites.size();
		//sprites[0].draw();
	//iterate through vector & draw all sprites
	};
	vector<Sprite> sprites; //array of all sprites

};


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem s) {
		//Emitter holds a SpriteSystem
		sys = s;
	};
	void draw() {
		//draws the Emitter
		ofVec2f pos;
		ofSetColor(ofColor::red);
		ofDrawRectangle(pos, 5, 5);
	};
	void start() {
		Sprite sprite;
		sys.add(sprite);
	}; //create sprites depending on the rate
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage); //refers to sprites that come out of the emitter
	void setImage(ofImage);
	void setRate(float);
	void update() {
	//only updates if started, otherwise return nothing
	//if started n called, checked ellapsedTime & firing them based off of rate
		//creates new sprite & gives it image, velocity, lifespan; can put all in constructor parameters, or use set methods
	};
	SpriteSystem sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage; //sprite image
	ofImage image;
	bool drawable; //visibility flag; don't draw if false
	bool haveChildImage;
	bool haveImage;
	float width, height;
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
		
		SpriteSystem sys; 
		Emitter emitter = Emitter(sys);
	
};
