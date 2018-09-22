#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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

	//use this to change position of the graphic
	void setPosition(ofVec3f p) { 
		trans = p; }
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	//ofVec2f pos;
	Sprite() {
		
	};

	void draw()	{
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

	void setImage(ofImage i) { //!not sure how this works
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
	
		image.load("jar.png");
		ofImage gun = image;
		childImage.load("cookie.png");
		ofImage bullet = childImage;
		setChildImage(bullet);
		setImage(gun);

	};

	void draw() {
		//draws the Emitter
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

	void setLifespan(float l) {
		lifespan = l;
	};

	void setVelocity(int v) {
		velocity.y = -v;
	};

	void setChildImage(ofImage c) {
		childImage = c;
		haveChildImage = true;
	}; //refers to sprites that come out of the emitter

	void setImage(ofImage i) {
		image = i;
		haveImage = true;
	};

	void setRate(float r) {
		rate = r;
	};

	void shoot() {	//create sprite
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

		if (started && shooting && (ofGetElapsedTimeMillis() - lastSpawned) > (1000/rate)) {
				shoot();	
			}

		sys.update();

		}

	//only updates if started, otherwise return nothing
	//if started n called, checked ellapsedTime & firing them based off of rate
		//creates new sprite & gives it image, velocity, lifespan; can put all in constructor parameters, or use set methods
	

	void translate(int x, int y) {
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
	
};
