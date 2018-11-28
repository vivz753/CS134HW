#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "TransformObject.h"
#include "ParticleSystem.h"

typedef enum { DirectionalEmitter, RadialEmitter, SphereEmitter, DiscEmitter } EmitterType;

//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class ParticleEmitter : public TransformObject {
public:
	ParticleEmitter();
	ParticleEmitter(ParticleSystem *s);
	~ParticleEmitter();
	void init();
	void draw();
	void start();
	void stop();
	void setLifespan(const float life)   { lifespan = life; }
	void setVelocity(const ofVec3f &vel) { velocity = vel; }
	void setRate(const float r) { rate = r; }
	void setParticleRadius(const float r) { particleRadius = r; }
	void setEmitterType(EmitterType t) { type = t; }
	void setGroupSize(int s) { groupSize = s; }
	void setOneShot(bool s) { oneShot = s; }
	void setRandomLife(bool b) { randomLife = b;  }
	void setLifespanRange(const ofVec2f &r) { lifeMinMax = r; }
	void setMass(float m) { mass = m; }
	void setDamping(float d) { damping = d; }
	void update();
	void spawn(float time);
	ParticleSystem *sys;
	float rate;         // per sec
	bool oneShot;
	bool fired;
	bool randomLife;
	ofVec3f lifeMinMax;
	ofVec3f velocity;
	float lifespan;     // sec
	float mass;
	float damping;
	bool started;
	float lastSpawned;  // ms
	float particleRadius;
	ofColor particleColor;
	float radius;
	bool visible;
	int groupSize;      // number of particles to spawn in a group
	bool createdSys;
	EmitterType type;
};
