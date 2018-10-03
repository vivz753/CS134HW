#include "ofMain.h"
#include "Emitter.h"


Emitter::Emitter(SpriteSystem s)
{
	shootSound.load("light.mp3");
	sys = s;
	width = 50;
	height = 50;
	started = false;
	shooting = false;
	haveImage = false;
	haveChildImage = false;

};

void Emitter::draw() {
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

void Emitter::start() {
	this->started = true;
	cout << "started" << endl;

};

void Emitter::stop() {
	this->started = false;
	cout << "stopped" << endl;
};

void Emitter::setLifespan(float l) {
	lifespan = l;
};

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
};

void Emitter::setChildImage(ofImage c) {
	childImage = c;
	haveChildImage = true;
};

void Emitter::setImage(ofImage i) {
	image = i;
	haveImage = true;
};

void Emitter::setRate(float r) { //set firing rate of sprites
	rate = r;
};

void Emitter::shoot() {
	shootSound.play();
	lastSpawned = ofGetElapsedTimeMillis();
	Sprite * sprite = new Sprite();
	sprite->width = 15;
	sprite->height = 15;
	ofVec3f centered = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
	sprite->setPosition(centered);
	sprite->lifespan = lifespan;
	sprite->velocity = velocity;
	sprite->setImage(childImage);
	sprite->birthtime = lastSpawned;
	sys.add(*sprite);
};

void Emitter::update() {
	if (started && shooting) {
		if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) shoot();
	}
	sys.update();
};

void Emitter::translate(int x, int y) {
	if (x < (ofGetWindowWidth() - width) && x > 0 && y < (ofGetWindowHeight() - height) && y >0) {
		trans.x = x;
		trans.y = y;
	}
};





