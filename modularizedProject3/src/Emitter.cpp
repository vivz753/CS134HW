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
		childImage.load("pumpkincat.png");
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
		totalHp = 3000;
		hp = 3000;

		trans = ofVec3f(ofGetWindowWidth() / 2 - 150, 50, 0);
		width = 300;
		height = 300;
		childWidth = 50;
		childHeight = 50;
		rate = .5;
		lifespan = -1;
		velocity = ofVec3f(0, 100, 0);

		childImage.load("skull.png");
		parentImage.load("pumpkincat.png");

		//area to detect collision
		rectangle = ofRectangle(trans, width, height);

		hpBar = ofRectangle(ofVec3f(trans.x, trans.y + height + 15), width, 5);

		break;
	case GUN:
		//holds the particleEmitter for explosion effect upon collision
		totalHp = 500;
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

		//area to detect collision
		rectangle = ofRectangle(trans, width, height);

		hpBar = ofRectangle(ofVec3f(trans.x, trans.y + height + 15), width, 5);
 		break;
	}
	
	
}

void Emitter::draw() {

		//ofDrawRectangle(rectangle.getPosition(), rectangle.getHeight(), rectangle.getWidth());
		parentImage.draw(trans, width, height);

		//green hp if more than 50%
		if (hp > totalHp/2) {
			ofSetColor(0, 255, 0);
		}
		//yellow hp if less than or equal to 50%
		else if (hp <= totalHp/2 && hp>totalHp/4) {
			ofSetColor(255, 255, 0);
		}
		//red hp if less than or equal to 25%
		else if (hp <= totalHp/4) {
			ofSetColor(255, 0, 0);
		}
		ofDrawRectangle(hpBar);
		ofSetColor(255, 255, 255);


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
		sprite = setSpriteSettings(sprite);
		break;
	case EMITTERB:
		sprite = new Sprite(B);
		sprite = setSpriteSettings(sprite);
		break;
	case EMITTERC:
		sprite = new Sprite(C);
		sprite = setSpriteSettings(sprite);

		break;
	case GUN:
		sprite = new Sprite(BULLET);
		sprite = setSpriteSettings(sprite);

		//spawnPoint is from the top of sprite instead of the default bottom--which is used for monster emitters
		ofVec3f spawnPoint = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
		sprite->setPosition(spawnPoint);
		break;
	}	

	
	sys->add(*sprite);
};

Sprite * Emitter::setSpriteSettings(Sprite * sprite) {
	sprite->setImage(childImage);
	sprite->width = childWidth;
	sprite->height = childHeight;
	sprite->rectangle.setWidth(childWidth);
	sprite->rectangle.setHeight(childHeight);

	ofVec3f spawnPoint = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y + height);
	sprite->setPosition(spawnPoint);

	sprite->lifespan = lifespan;
	sprite->velocity = velocity;

	lastSpawned = ofGetElapsedTimeMillis();
	sprite->birthtime = lastSpawned;

	return sprite;
}

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
		hpBar.setWidth((hp/totalHp) * width);
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
			if ((ofGetElapsedTimeMillis() - lastSpawned) > (1000 / rate)) {
				shoot();
			}
			sinMovement = ofMap(sin(ofGetElapsedTimef()), -1, 1, 200, 500);
			trans = ofVec3f(sinMovement,50,0);
		}

		hpBar.setPosition(ofVec3f(trans.x, trans.y + height + 10));
		hpBar.setWidth((hp / totalHp) * width);
		rectangle.setPosition(trans);
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


void Emitter::checkCollision(SpriteSystem * enemySprites) {
	for (vector<Sprite>::iterator i = enemySprites->sprites.begin(); i != enemySprites->sprites.end(); i++) {
		if (i->rectangle.intersects(rectangle)) {
			i->lifespan = 1;
			hp -= 50;
		}
		
	}

};

void Emitter::checkCollision(Emitter enemyEmitter) {
		if (enemyEmitter.rectangle.intersects(rectangle)) {
			hp -= 50;
		}


};