#include "ofxBox2dRect.h"

#pragma once

namespace Box2dArena {

class Target: public ofxBox2dRect {
public:
	virtual ~Target();
	Target();

	virtual void draw();

	bool bHit, bEnteredArena;
	ofColor color;
protected:

};

} /* namespace Box2dArena */
