#include "Emitter.h"

Emitter::Emitter() {
	sys = new SpriteSystem();
	emitting = false;
	rectangle = ofRectangle(ofVec3f(0, 0, 0), 0, 0);
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
		
		trans = ofVec3f(20, 0, 0);
		width = 50;
		height = 50;
		rate = 5;
		lifespan = 1500;
		velocity = ofVec3f(0, 300, 0);
		//delete parentImagelater
		//parentImage.load("cookie.png");
		childImage.load("spriteA.png");
		cout << "emitterA init" << endl;
		
		//set sprites 
		break;
	case EMITTERB:
		//childImage.load("skull.png");
		trans = ofVec3f(20, 0, 0);
		width = 50;
		height = 50;
		rate = 5;
		lifespan = 1500;
		velocity = ofVec3f(0, 300, 0);
		//delete parentImagelater
		//parentImage.load("cookie.png");
		childImage.load("skull.png");
		cout << "emitterB init" << endl;
		break;
	case EMITTERC:
		//childImage.load("pokeball.png");
		rate = 5;




		//fill me out





		//
		break;
	case GUN:
		hp = 500;
		trans = ofVec3f(400, 400, 0);
		width = 50;
		height = 50;
		rate = 5;
		lifespan = 1500;
		velocity = ofVec3f(0, -300, 0);
		parentImage.load("bow.png");
		childImage.load("arrow.png");
		cout << "gun init" << endl;

		rectangle = ofRectangle(trans, width, height);

		hpBar = ofRectangle(ofVec3f(trans.x, trans.y + height + 15), width, 5);
 		break;
	}
	
	
}

void Emitter::draw() {
	if (emitterType == GUN) {
		ofDrawRectangle(rectangle.getPosition(), rectangle.getHeight(), rectangle.getWidth());
		parentImage.draw(trans, width, height);

		ofSetColor(0,255,0);
		ofDrawRectangle(hpBar);
		ofSetColor(255, 255, 255);
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

	//sets the image
	sprite->setImage(childImage);
	//sprite->init();

	//centers the position of the childSprite to come out of the center of the emitter
	ofVec3f centered = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
	sprite->setPosition(centered);

	
	sprite->lifespan = lifespan;
	sprite->velocity = velocity;
	
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
		
		hpBar.setPosition(ofVec3f(trans.x, trans.y + height + 10));
		hpBar.setWidth((hp/500) * width);
		rectangle.setPosition(trans);

		/*if (moving) {
			translate(movingVector);
		}*/
		break;
	case EMITTERA:
		if (emitting) {
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
			trans = ofVec3f(ofRandom(0, ofGetWindowWidth() - 50), 0, 0);
		}
		break;
	case EMITTERB:
		if (emitting) {
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
			trans = ofVec3f(ofRandom(0, ofGetWindowWidth() - 50), 0, 0);
			cout << "updating emitter B" << endl;
		}
		break;
	case EMITTERC:
		if (emitting) {

		}
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

void Emitter::checkCollision(SpriteSystem * enemySprites) {
	for (vector<Sprite>::iterator i = enemySprites->sprites.begin(); i != enemySprites->sprites.end(); i++) {
		if (i->rectangle.intersects(rectangle)) {
			i->lifespan = 1;
			hp -= 15;
		}
		
	}

};