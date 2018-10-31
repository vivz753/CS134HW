#include "Emitter.h"

Emitter::Emitter() {
	sys = new SpriteSystem();
	emitting = false;
}

Emitter::Emitter(EmitterType eType) {
	emitterType = eType;
	sys = new SpriteSystem();
	emitting = false;
};

void Emitter::setPosition(ofVec3f p) {
	trans = p;
};

void Emitter::init() {
	switch (emitterType) {
	case EMITTERA:
		//childImage.load("cookie.png");
		trans = ofVec3f(20, 20, 0);
		rate = 5;
		
		//set sprites 
		break;
	case EMITTERB:
		//childImage.load("skull.png");
		rate = 5;
		break;
	case EMITTERC:
		//childImage.load("pokeball.png");
		rate = 5;
		break;
	case GUN:
		trans = ofVec3f(400, 400, 0);
		width = 50;
		height = 50;
		rate = 5;
		lifespan = 5;
		velocity = ofVec3f(0, -500, 0);
		parentImage.load("bow.png");
		childImage.load("arrow.png");
		cout << "gun init" << endl;
 		break;
	}
	
	
}

void Emitter::draw() {
	if (emitterType = GUN) {
		parentImage.draw(trans, width, height);
		
	}
	sys->draw();
};

void Emitter::start() {
	emitting = true;
}

void Emitter::stop() {
	emitting = false; 
}

void Emitter::shoot() {

	Sprite * sprite;

	//init sprite depending on type of enemy
	switch (emitterType) {
	case EMITTERA:
		sprite = new Sprite(A);
		/*lifespan = 5;
		velocity = ofVec3f(0, -5, 0);*/
		break;
	case EMITTERB:
		sprite = new Sprite(B);
		/*lifespan = 10;
		velocity = ofVec3f(0, -5, 0);*/
		break;
	case EMITTERC:
		sprite = new Sprite(C);
		/*lifespan = -1;
		velocity = ofVec3f(0, -5, 0);*/
		break;
	case GUN:
		sprite = new Sprite(BULLET);
		break;
	}	

	
	ofVec3f centered = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
	sprite->setPosition(centered);

	
	sprite->lifespan = lifespan;
	sprite->velocity = velocity;
	

	//set image based on type of enemy emitter
	lastSpawned = ofGetElapsedTimeMillis();
	sprite->birthtime = lastSpawned;
	sys->add(*sprite);
};

void Emitter::update() {
	switch (emitterType) {
	case GUN:
		//shoot at a steady rate
		if (emitting) {
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
		}
		/*if (moving) {
			translate(movingVector);
		}*/
		break;
	case EMITTERA:
		break;
	case EMITTERB:
		break;
	case EMITTERC:
		break;
	}
	sys->update();
};

//translate the Emitter with mouse coordinates
void Emitter::translate(int x, int y) {
	if (x < (ofGetWindowWidth() - width) && x > 0 && y < (ofGetWindowHeight() - height) && y >0) {
		trans.x = x;
		trans.y = y;
	}
};

////translate the Emitter using WASD keys
//void Emitter::translate(ofVec3f v) {
//	ofVec3f newPos = trans + v / ofGetFrameRate();
//	if (newPos.x < (ofGetWindowWidth() - width) && newPos.x>0 && newPos.y < (ofGetWindowHeight() - height) && newPos.y>0) {
//		trans += v / ofGetFrameRate();
//	}
//};
