#include "ofxBox2dRect.h"

#pragma once

namespace Box2dArena {

class Target: public ofxBox2dRect {
public:
	Target();
	virtual ~Target();

	void setup(b2World * b2dworld, float x, float y);

	static void loadImages();

	virtual void draw(bool debug = false);

	bool bHit, bEnteredArena, bMissed;
	ofColor color;
protected:
	ofImage *img, *brokenImg;
	static vector<ofImage> images;
	static vector<ofImage> brokenImages;
	static bool imagesLoaded;
};

} /* namespace Box2dArena */
