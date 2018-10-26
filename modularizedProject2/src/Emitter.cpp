#include "ofMain.h"
#include "Emitter.h"


Emitter::Emitter()
{
	sys = SpriteSystem();
	haveImage = false;
	haveChildImage = false;
	
};

void Emitter::gunInit() {
	shootSound.load("light.mp3");
	width = 50;
	height = 50;
	started = false;
	shooting = false;
	enemyEmitter = false; 
	velocity = ofVec3f(0, -500, 0);
	rate = 5;
	lifespan = 1500;
	hp = 200;
	score = 0;
	dead = false;
};

void Emitter::enemiesInit(float size) {
	//trans = ofVec3f(500, 0);
	velocity = ofVec3f(0, 450, 0);
	rate = 2;
	width = size;
	height = size;
	started = false;
	shooting = true;
	enemyEmitter = true;
	lifespan = 1500;
};

void Emitter::draw() {
	if (started) {
		if (!haveImage) {			
			//ofDrawRectangle(trans, width, height);
		}
		else {

			//eventually implement rotation by cursor to have 360 degree aiming & shooting
			/*if (!enemyEmitter) {
				ofPushMatrix();
				ofRotate(10);*/

				image.draw(trans, width, height);
				/*ofPopMatrix();
				
			}*/
			
		}
		sys.draw();
	}
};

void Emitter::start() {
	dead = false;
	this->started = true;
	hp = 200;
	score = 0;
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
	//shootSound.play();
	lastSpawned = ofGetElapsedTimeMillis();
	Sprite * sprite = new Sprite();
	if (enemyEmitter) {
		sprite->width = 50;
		sprite->height = 50;
	}
	else {
		sprite->width = 50;
		sprite->height = 50;
	}
	
	ofVec3f centered = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
	sprite->setPosition(centered);
	sprite->lifespan = lifespan;
	sprite->velocity = velocity;
	sprite->setImage(childImage);
	sprite->birthtime = lastSpawned;
	sys.add(*sprite);
};

void Emitter::update() {
	if ((started && shooting) || enemyEmitter) {
		if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) shoot();
	}

	//have the enemy emitters move around randomly
	if (enemyEmitter) {
		trans = ofVec3f(ofRandom(0, ofGetWindowWidth() -50), 0, 0) ;
	}

	if (moving) {
		translate(movingVector);
	}
	sys.update();
};

//translate the Emitter with mouse coordinates
void Emitter::translate(int x, int y) {
	if (x < (ofGetWindowWidth() - width) && x > 0 && y < (ofGetWindowHeight() - height) && y >0) {
		trans.x = x;
		trans.y = y;
	}
};

//translate the Emitter using WASD keys
void Emitter::translate(ofVec3f v) {
	ofVec3f newPos = trans + v/ofGetFrameRate();
	if (newPos.x < (ofGetWindowWidth() - width) && newPos.x>0 && newPos.y < (ofGetWindowHeight() - height) && newPos.y>0) {
		trans += v / ofGetFrameRate();
	}
};



float Emitter::maxDistPerFrame() {
	
	return  velocity.length() / ofGetFrameRate();
}

//check to see if enemies collided with the Emitter, if so reduce the hp
bool Emitter::collided(ofVec3f point, float dist) {
	ofVec3f v = trans - point;
	if (v.length() < 50) {
		hp -= 25;
		cout << hp << endl;
		return true;
	}
	return false;
}






