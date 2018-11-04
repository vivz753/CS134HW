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
	init();
};

void Emitter::setPosition(ofVec3f p) {
	trans = p;
};

void Emitter::init() {
	switch (emitterType) {
	case EMITTERA:
		
		trans = ofVec3f(0, 0, 0);
		width = 25;
		height = 25;
		childWidth = 50;
		childHeight = 50;
		rate = 2;
		lifespan = 1500;
		velocity = ofVec3f(0, 250, 0);
		childImage.load("skull.png");
		cout << "emitterA init" << endl;
		
		 
		break;
	case EMITTERB:
		

		//positioned at center of screen
		trans = ofVec3f(ofGetWindowWidth() / 2, 0, 0);
		width = 50;
		height = 50;
		childWidth = 50;
		childHeight = 50;
		rate = .5;
		lifespan = 9000;
		velocity = ofVec3f(0, 100, 0);
	
		childImage.load("skull.png");

		cout << "emitterB init" << endl;
		break;
	case EMITTERC:
		
		trans = ofVec3f(ofGetWindowWidth() / 2, 350, 0);
		width = 300;
		height = 300;
		childWidth = 50;
		childHeight = 50;
		rate = .5;
		lifespan = 9000;
		velocity = ofVec3f(0, 100, 0);

		childImage.load("skull.png");
		parentImage.load("pumpkincat.png");

		//fill me out





		//
		break;
	case GUN:
		//holds the particleEmitter for explosion effect upon collision
		hp = 500;
		trans = ofVec3f(400, 400, 0);
		width = 50;
		height = 50;
		childWidth = 15;
		childHeight = 50;
		rate = 5;
		lifespan = 1500;
		velocity = ofVec3f(0, -300, 0);
		parentImage.load("bow.png");
		childImage.load("thinarrow.png");
		cout << "gun init" << endl;

		rectangle = ofRectangle(trans, width, height);

		hpBar = ofRectangle(ofVec3f(trans.x, trans.y + height + 15), width, 5);
 		break;
	}
	
	
}

void Emitter::draw() {
	if (emitterType == GUN || EMITTERC) {
		//ofDrawRectangle(rectangle.getPosition(), rectangle.getHeight(), rectangle.getWidth());
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
		break;
	case EMITTERB:
		sprite = new Sprite(B);
		break;
	case EMITTERC:
		sprite = new Sprite(C);
		break;
	case GUN:
		sprite = new Sprite(BULLET);
		break;
	}	

	//sets the image
	sprite->setImage(childImage);
	sprite->width = childWidth;
	sprite->height = childHeight;
	sprite->rectangle.setWidth(childWidth);
	sprite->rectangle.setHeight(childHeight);
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
	float sinMovement;

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
		break;
		//EMITTER A moves randomly along the x-axis at the top & releases sprites at rate 
	case EMITTERA:
		if (emitting) {
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
			trans = ofVec3f(ofRandom(0, ofGetWindowWidth() - 50), 0, 0);
		}
		break;

		//EMITTER B releases sprites that move in a sin wave
	case EMITTERB:
		if (emitting) {
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
			
			//sinMovement = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, ofGetWidth() - 50);
			//trans = ofVec3f(sinMovement,0,0);

			//trans = ofVec3f(0, ofGetWindowWidth() / 2 - 25, 0);

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
			hp -= 50;
		}
		
	}

};