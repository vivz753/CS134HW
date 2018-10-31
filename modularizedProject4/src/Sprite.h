#pragma once
#include "ofMain.h"

typedef enum { A, B, C, WEAPON, BULLET } SpriteType;

class Sprite {
public:
	Sprite();
	Sprite(SpriteType);
	SpriteType spriteType;

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
	
};

class SpriteSystem {
public:
	vector<Sprite> sprites;

	void add(Sprite s) {
		sprites.push_back(s);
		s.name = "s" + to_string(sprites.size());
	};

	void remove(int i) {
		sprites.erase(sprites.begin() + i);
	};

	void remove(vector<Sprite>::iterator & i) {
		i->lifespan = 1;
	};

	bool collided(ofVec3f point, float dist) {
		vector<Sprite>::iterator s = sprites.begin();
		while (s != sprites.end()) {
			ofVec3f v = s->trans - point;
			if (v.length() < dist) {
				return true;
			}
		}
	};

	bool removeNear(ofVec3f point, float dist) {
		bool erased = false;
		vector<Sprite>::iterator s = sprites.begin();

		while (s != sprites.end()) {
			ofVec3f v = s->trans - point;
			if (v.length() < 50) {
				s = sprites.erase(s);
				erased = true;
			}
			else s++;
		}
		return erased;
	};

	void update() {
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
			//cout << "trans: " << sprites[i].trans << endl;
		}

		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors


	};

	void draw() {
		for (size_t i = 0; i < sprites.size(); i++) {
			sprites[i].draw();
		}
		//cout << "drawing" << endl;
	};


};