#pragma once
#include "ofMain.h"

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
	vector<Sprite> sprites;

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


	////check if this SpriteSystem's sprites' rectangles (enemies) collid with an Emitter's rectangle
	//void checkCollisions(ofRectangle emitterRectangle) {
	//	for (vector<Sprite>::iterator i = sprites.begin(); i != sprites.end(); i++) {
	//		if (i->rectangle.intersects(emitterRectangle)) {
	//			i->lifespan = 1;
	//		}
	//	}
	//}

	//check if this SpriteSystem's sprites (bullets) collide with another SpriteSystem's sprites (enemies)
	void SpriteSystem::checkCollisions(SpriteSystem * enemySprites) {
		for (vector<Sprite>::iterator i = sprites.begin(); i != sprites.end(); i++) {
			for (vector<Sprite>::iterator j = enemySprites->sprites.begin(); j != enemySprites->sprites.end(); j++) {
				if (i->rectangle.intersects(j->rectangle)) {
					i->lifespan = 1;
					j->lifespan = 1;
				}
			}
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
				tmp = sprites.erase(s);	//not sure what this does
				s = tmp;
			}
			else s++;
		}

		for (size_t i = 0; i < sprites.size(); i++) {
			sprites[i].trans += sprites[i].velocity / ofGetFrameRate();

			//testing rectangle of sprites
			sprites[i].rectangle.setPosition(sprites[i].trans);
			//cout << "trans: " << sprites[i].trans << endl;
		}

		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors


	};

	void SpriteSystem::draw() {
		for (size_t i = 0; i < sprites.size(); i++) {
			
			//eventually delete to make square invisible
			ofDrawRectangle(sprites[i].rectangle.getPosition(), sprites[i].rectangle.getHeight(), sprites[i].rectangle.getWidth());

			sprites[i].draw();

		}
		//cout << "drawing" << endl;
	};


};