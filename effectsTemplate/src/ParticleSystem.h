#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"

typedef enum { Gravity, Turbulence, ImpulseRadial } ForceType;

//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
protected:
public:
	ForceType type;
	bool applyOnce = false;
	bool applied = false;
	//void updateForce(Particle *);
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	int minHeight;
	int maxHeight;
	void setHeight(int, int);
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
	void setLifespan(float);
	void reset();
	int removeNear(const ofVec3f & point, float dist);
	void draw();
	vector<Particle> particles;
	vector<ParticleForce *> forces;
};



// Some convenient built-in forces
//
class GravityForce: public ParticleForce {
	ofVec3f gravity;
public:
	GravityForce(const ofVec3f & gravity);
	void updateForce(Particle *);
};

class TurbulenceForce : public ParticleForce {
	ofVec3f tmin, tmax;
public:
	TurbulenceForce(const ofVec3f & min, const ofVec3f &max);
	void updateForce(Particle *);
};

class ImpulseRadialForce : public ParticleForce {
	float magnitude;
	int min;
	int max;
public:
	ImpulseRadialForce(float magnitude, int, int);
	void updateForce(Particle *);
	
};
