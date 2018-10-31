#include "Emitter.h"


Emitter::Emitter(EmitterType eType) {
	emitterType = eType;
	sys = new SpriteSystem();
	lifespan;
	velocity;
};

void Emitter::init() {
	//switch (emitterType) {
	//case EMITTERA:
	//	childImage.load("cookie.png");
	//	setChildImage(childImage);
	//	//set sprites 
	//	break;
	//case EMITTERB:
	//	childImage.load("skull.png");
	//	setChildImage(childImage);
	//	break;
	//case EMITTERC:
	//	childImage.load("pokeball.png");
	//	setChildImage(childImage);
	//	break;
	//case GUN:
	//	gunImage.load("bow.png");
	//	setImage(gunImage);
	//	childImage.load("arrow.png");
	//	setChildImage(childImage);
	//	//set image of gun 
	//	break;
	//}
	//
	
}

void Emitter::draw() {
	if (emitterType = GUN) {
		gunImage.draw(trans, width, height);
	}
	sys->draw();
};

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
	sys->add(*sprite);
};


