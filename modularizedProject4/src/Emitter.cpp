#include "Emitter.h"

Emitter::Emitter(EmitterType e) {
	emitterType = e;
	sys = new SpriteSystem();
	
};

void Emitter::init() {
	cout << "blah" << endl;
};