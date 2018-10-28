#include "Emitter.h"


Emitter::Emitter(EmitterType eType) {
	emitterType = eType;
	sys = SpriteSystem();
	lifespan;
	velocity;
}

void Emitter::init() {
	switch (emitterType) {
	case EMITTERA:
		//set sprites 
		break;
	case EMITTERB:
		break;
	case EMITTERC:
		break;

	case GUN:
		//set image of gun 
		break;
	}
}

void Emitter::draw() {
	if (emitterType = GUN) {
		image.draw(trans, width, height);
	}
	sys.draw();
}

void Emitter::shoot() {
	
	Sprite * sprite;

	//init sprite depending on type of enemy
	switch (emitterType) {
	case EMITTERA:
		sprite = new Sprite(A);
		//sprite->setImage(imageA);
		break;
	case EMITTERB:
		sprite = new Sprite(B);
		//sprite->setImage(imageB);
		break;
	case EMITTERC:
		sprite = new Sprite(C);
		//sprite->setImage(imageC);
		break;
	}	
	
	ofVec3f centered = ofVec3f(trans.x + width / 2 - sprite->width / 2, trans.y);
	sprite->setPosition(centered);

	sprite->lifespan = lifespan;
	sprite->velocity = velocity;
	

	//set image based on type of enemy emitter
	
	sprite->birthtime = ofGetElapsedTimeMillis();
	sys.add(*sprite);
}


