#pragma once
#include "ofMain.h"

class BaseObject {
public:
	BaseObject() {
		trans = ofVec2f(0, 0);
		scale = ofVec2f(1);
		rot = 0;
	};
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;

	//use this to change position of the graphic
	void setPosition(ofVec3f p) {
		trans = p;
	}
};

class Sprite : public BaseObject {
public:
	//ofVec2f pos;
	Sprite();
	void draw();
	float age();
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name; //give names to sprite for debugging purposes
	bool haveImage;
	float width, height;
};



class SpriteSystem {
public:

	//adds sprites to the vector array
	void add(Sprite s) {

		sprites.push_back(s);
		s.name = "spr" + to_string(sprites.size());

	};

	//removes sprite at index[int]
	void remove(int i) {
		sprites.erase(sprites.begin() + i);
	};

	void remove(vector<Sprite>::iterator & i) {
		i->lifespan = 1;
	}


	bool collided(ofVec3f point, float dist) {
		vector<Sprite>::iterator s = sprites.begin();
		while (s != sprites.end()) {
			ofVec3f v = s->trans - point;
			if (v.length() < dist) {
				return true;
			}
		}
	}
	//removes sprites that are near 
	bool removeNear(ofVec3f point, float dist) {
		bool erased = false;
		vector<Sprite>::iterator s = sprites.begin();
		//vector<Sprite>::iterator tmp;
		while (s != sprites.end()) {
			ofVec3f v = s->trans - point;
			
			if (v.length() < 50) {
				s = sprites.erase(s);
				//s->lifespan = 1;
				erased = true;
				//s = tmp;
			}
			else s++;
		}
		return erased;
	}

	void update() {

		if (sprites.size() == 0) return;
		vector<Sprite>::iterator s = sprites.begin();
		vector<Sprite>::iterator tmp;

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

		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
			//cout << "trans: " << sprites[i].trans << endl;
		}

		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors
	};
	void draw() {
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].draw();
		}
		//cout << "drawing" << endl;
	};
	vector<Sprite> sprites; //array of all sprites

};
