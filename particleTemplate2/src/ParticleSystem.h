#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"


//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
public:
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
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

	//*Method to set the 'gravity' 3dvector variable of a Gravity Force object
	void setGravity(ofVec3f g) {
		gravity = g;
	}
	
};

class TurbulenceForce : public ParticleForce {
	ofVec3f tmin, tmax;
public:
	TurbulenceForce(const ofVec3f & min, const ofVec3f &max);
	void updateForce(Particle *);
};
