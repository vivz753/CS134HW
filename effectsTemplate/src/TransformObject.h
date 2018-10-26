#pragma once
#include "ofMain.h"

//  Kevin M. Smith - CS 134 SJSU
//

//  Base class for any object that needs a transform.
//
class TransformObject {
protected:
	TransformObject();
	ofVec3f position, scale;
	float	rotation;
	bool	bSelected;
	void setPosition(const ofVec3f &);
};