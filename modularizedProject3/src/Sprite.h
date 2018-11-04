#pragma once
#include "ofMain.h"
#include "ParticleEmitter.h"

typedef enum { A, B, C, WEAPON, BULLET } SpriteType;

class Sprite {
public:
	Sprite();
	Sprite(SpriteType);
	SpriteType spriteType;
	void init();

	float width, height;
	ofImage image;
	//bool haveImage;
	void setImage(ofImage);
	void draw();
	
	ofVec3f trans;
	void setPosition(ofVec3f);

	float birthtime;
	float lifespan;
	float age();
	
	ofVec3f velocity;
	
	string name;

	ofRectangle rectangle;
	
};

class SpriteSystem {
public:
	ofVec3f collidedVector;
	vector<Sprite> sprites;
	bool collided;
	bool appliedSinMovement;
	bool normalSinMovement;
	bool inverseSinMovement;

	void SpriteSystem::add(Sprite s) {
		sprites.push_back(s);
		s.name = "s" + to_string(sprites.size());
	};

	void SpriteSystem::remove(int i) {
		sprites.erase(sprites.begin() + i);
	};

	void SpriteSystem::remove(vector<Sprite>::iterator & i) {
		i->lifespan = 1;
	};

	ofVec3f SpriteSystem::returnCollidedVector() {
		return collidedVector;
	}


	//check if this SpriteSystem's sprites (bullets) collide with another SpriteSystem's sprites (enemies)
	float SpriteSystem::checkCollisions(SpriteSystem * enemySprites, ParticleEmitter * pe) {
		float score = 0;
		for (vector<Sprite>::iterator i = sprites.begin(); i != sprites.end(); i++) {
			for (vector<Sprite>::iterator j = enemySprites->sprites.begin(); j != enemySprites->sprites.end(); j++) {
				if (i->rectangle.intersects(j->rectangle)) {
					//collided = true;
					collidedVector = ofVec3f(i->rectangle.getPosition().x + i->rectangle.getWidth()/2, i->rectangle.getPosition().y+ i->rectangle.getHeight()/2, 0);


					//remove bullet sprites
					i->lifespan = 1;

					//remove enemy sprites
					j->lifespan = 1;

					//add 50 pts to playerScore
					score = 50;
					
					pe->setPosition(collidedVector);
					pe->start();
				}
				//else collided = false;
			}
		}
		//return collided;
		return score;
	}

	void SpriteSystem::applySinMovement(int i) {
		appliedSinMovement = true;
		if (i > 0) {
			normalSinMovement = true;
		}
		else {
			inverseSinMovement = true;
		}
	}

	void SpriteSystem::update() {
		if (sprites.size() == 0) return;
		vector<Sprite>::iterator s = sprites.begin();
		vector <Sprite>::iterator tmp;

		// check which sprites have exceed their lifespan and delete
		// from list.  When deleting multiple objects from a vector while
		// traversing at the same time, use an iterator.
		//
		while (s != sprites.end()) {
			if (s->lifespan > 0 && s->age() > s->lifespan) {
				//          cout << "deleting sprite: " << s->name << endl;
				tmp = sprites.erase(s);	
				s = tmp;
			}
			else s++;
		}

		for (size_t i = 0; i < sprites.size(); i++) {
			if (appliedSinMovement) {
			
				if (normalSinMovement) {
					float sinValue = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, ofGetWidth() - 50);
					sprites[i].trans.x = sinValue;
				}

				else if (inverseSinMovement) {
					float cosValue = ofMap(cos(ofGetElapsedTimef()), -1, 1, 0, ofGetWidth() - 50);
					sprites[i].trans.x = cosValue;
				}
				sprites[i].trans.y += sprites[i].velocity.y / ofGetFrameRate();
			}
			else {
				sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
			}
			

			//rectangle of sprites used to detect collision (ofRectangle intersect())
			sprites[i].rectangle.setPosition(sprites[i].trans);
			//cout << "trans: " << sprites[i].trans << endl;
		}

		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors
	};

	void SpriteSystem::draw() {
		for (size_t i = 0; i < sprites.size(); i++) {
			
			//eventually delete to make square invisible
			//ofDrawRectangle(sprites[i].rectangle.getPosition(), sprites[i].rectangle.getHeight(), sprites[i].rectangle.getWidth());

			sprites[i].draw();

		}
		
	};


};