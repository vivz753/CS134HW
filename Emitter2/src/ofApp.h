//DESCRIPTION:
//Project 1 submission by Vivian Leung for Prof. Kevin Smith's CS134 at SJSU

//INSTRUCTIONS:
//Press spacebar to begin. Use mouse to move gun around. Press space or click to shoot bullets. Press q to quit.
//Slider GUI in top left corner can be used to adjust the rate, velocity, and lifespan of bullet sprites. 

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
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

	//use this to change position of the graphic
	void setPosition(ofVec3f p) { 
		trans = p; }
};

//  General Sprite class  (similar to a Particle)
class Sprite : public BaseObject {
public:
	//ofVec2f pos;
	Sprite() {
		
	};

	void draw()	{
		//draw a blue box by default if no image is set
		if (!haveImage) {
			ofSetColor(ofColor::blue);
			ofDrawRectangle(trans, width, height);
		}
		else {
			image.draw(trans, width, height);
		}
		};

	float age() {
		return ofGetElapsedTimeMillis() - birthtime;
	};

	void setImage(ofImage i) { 
		image = i;
		haveImage = true;
	};

	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name; //give names to sprite for debugging purposes
	bool haveImage;
	float width, height;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:

	//adds sprites to the vector array
	void add(Sprite s) {
		
		sprites.push_back(s);
		s.name = "spr" + to_string(sprites.size());
		
	};

	//removes sprite at index[int]
	void remove(int i) {
		sprites.erase(sprites.begin() + i);
	};

	void update() {

		if (sprites.size() == 0) return;
		vector<Sprite>::iterator s = sprites.begin();
		vector<Sprite>::iterator tmp;

		// check which sprites have exceed their lifespan and delete
		// from list.  When deleting multiple objects from a vector while
		// traversing at the same time, use an iterator.
		//
		while (s != sprites.end()) {
			if (s->lifespan > 0 && s->age() > s->lifespan) {
				//          cout << "deleting sprite: " << s->name << endl;
				tmp = sprites.erase(s);	//not sure what this does
				s = tmp;
			}
			else s++;
		}

		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
			//cout << "trans: " << sprites[i].trans << endl;
		}
		
		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors
	};
	void draw() {
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].draw();
		}
		//cout << "drawing" << endl;
	};
	vector<Sprite> sprites; //array of all sprites

};


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	ofSoundPlayer shootSound;
	Emitter(SpriteSystem s) {
		//Emitter holds a SpriteSystem
	
		shootSound.load("light.mp3");
		sys = s;
		width = 50;
		height = 50;
		started = false;
		shooting = false;
		haveImage = false;
		haveChildImage = false;
	
		

	};

	//draws the Emitter
	void draw() {
		if (started) {
			if (!haveImage) {
				ofSetColor(ofColor::red);
				ofDrawRectangle(trans, width, height);
			}
			else {
				image.draw(trans, width, height);
			}
			sys.draw();
		}
	};

	void start() {	//start the game
		started = true;
		cout << "started" << endl;

	}; 

	void stop() {	//stop the game
		started = false;
		cout << "stopped" << endl;
	};

	void setLifespan(float l) { //set lifespan of sprites
		lifespan = l;
	};

	void setVelocity(int v) { //set velocity of sprites
		velocity.y = -v;
	};

	void setChildImage(ofImage c) { //set image of sprites
		childImage = c;
		haveChildImage = true;
	}; 

	void setImage(ofImage i) { //set image of emitter
		image = i;
		haveImage = true;
	};

	void setRate(float r) { //set firing rate of sprites
		rate = r;
	};

	void shoot() {	//creates sprite, sets properties, adds to array
		shootSound.play();
			lastSpawned = ofGetElapsedTimeMillis();
			Sprite * sprite = new Sprite();
			sprite->width = 15;
			sprite->height = 15;
			ofVec3f centered = ofVec3f(trans.x + width/2 - sprite->width/2 , trans.y);
			sprite->setPosition(centered);
			sprite->lifespan = lifespan;
			sprite->velocity = velocity;
			sprite->setImage(childImage);
			sprite->birthtime = lastSpawned;
			sys.add(*sprite);
			

	}

	void update() { //shoots depending on the rate
		//only updates if started, otherwise return nothing
		//if started and called, checked ellapsedTime & firing them based off of rate
		//custom formula to determine how often to fire sprites
		if (started && shooting) {
			if((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) shoot();	
			}
		sys.update();

		}

	//move emitter according to mouse
	void translate(int x, int y) {
		//do not allow emitter to go outside window
		if (x < (ofGetWindowWidth() - width) && x > 0 && y < (ofGetWindowHeight()-height) && y >0) {
			trans.x = x;
			trans.y = y;
		}

	}

	bool shooting;	//set to true if user key is pressed down
	SpriteSystem sys;	//manager of sprites
	float rate;	//rate of firing sprites
	ofVec3f velocity; 
	float lifespan; //life span of sprites
	bool started; //draw the emitter & shoot stuff
	float lastSpawned; //time last sprite was spawned
	ofImage childImage; //sprite image
	ofImage image;	//emitter image
	bool drawable; //visibility flag; don't draw if false
	bool haveChildImage;
	bool haveImage;
	float width, height; //size of emitter, set in constructor
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
		
	
		Emitter emitter = Emitter(SpriteSystem());
		ofxFloatSlider firingRateSlider;
		ofxFloatSlider velocitySlider;
		ofxFloatSlider lifeSpanSlider;
		ofxPanel gui;
		bool pressingMouse;
		ofImage background;
		ofSoundPlayer bgMusic;
		ofTrueTypeFont text;

		ofImage gun;
		ofImage bullet;

	
};
