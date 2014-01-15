#include "ofxBox2dRect.h"

#pragma once

namespace Box2dArena {

class Target: public ofxBox2dRect {
public:
	Target();
	virtual ~Target();

	void setup(b2World * b2dworld, float x, float y);

	static void loadImages();

	virtual void draw();

	bool bHit, bEnteredArena;
	ofColor color;
protected:
	ofImage * img;
	static vector<ofImage> images;
	static bool imagesLoaded;
};

} /* namespace Box2dArena */
