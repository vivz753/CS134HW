#pragma once
#include "ofMain.h"

//  Kevin M. Smith - CS 134 SJSU
//

//  Base class for any object that needs a transform.
//
class TransformObject {
	
public:
	void setPosition(const ofVec3f &);

protected:
	TransformObject();
	ofVec3f position, scale;
	float	rotation;
	bool	bSelected;
	
};