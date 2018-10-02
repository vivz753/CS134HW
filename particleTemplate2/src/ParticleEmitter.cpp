
//  Kevin M. Smith - CS 134 SJSU

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {
	sys = new ParticleSystem();
	createdSys = true;
	init();
}

ParticleEmitter::ParticleEmitter(ParticleSystem *s) {
	if (s == NULL)
	{
		cout << "fatal error: null particle system passed to ParticleEmitter()" << endl;
		ofExit();
	}
	sys = s;
	createdSys = false;
	init();
}

ParticleEmitter::~ParticleEmitter() {

	// deallocate particle system if emitter created one internally
	//
	if (createdSys) delete sys;
}

void ParticleEmitter::init() {
	rate = 1;
	velocity = ofVec3f(0, 20, 0);
	lifespan = 3;
	started = false;
	lastSpawned = 0;
	radius = 1;
	particleRadius = .1;
	visible = true;
	type = DirectionalEmitter;
}



void ParticleEmitter::draw() {
	if (visible) {
		switch (type) {
		case DirectionalEmitter:
			ofDrawSphere(position, radius/10);  // just draw a small sphere for point emitters 
			break;
		case SphereEmitter:
		case RadialEmitter:
			ofDrawSphere(position, radius/10);  // just draw a small sphere as a placeholder
			break;
		default:
			break;
		}
	}
	sys->draw();  
}
void ParticleEmitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void ParticleEmitter::stop() {
	started = false;
}
void ParticleEmitter::update() {
	if (!started) return;

	float time = ofGetElapsedTimeMillis();

	if ((time - lastSpawned) > (1000.0 / rate)) {

		// spawn a new particle
		//
		Particle particle;

		// set initial velocity and position
		// based on emitter type
		//
		switch (type) {
		case RadialEmitter:
	//		break;
		case SphereEmitter:
	//		break;
		case DirectionalEmitter:
			particle.velocity = velocity;
			particle.position.set(position);
			break;
		}

		// other particle attributes
		//
		particle.lifespan = lifespan;
		particle.birthtime = time;
		particle.radius = particleRadius;

		// add to system
		//
		sys->add(particle);
		lastSpawned = time;
	}
	sys->update();
}

