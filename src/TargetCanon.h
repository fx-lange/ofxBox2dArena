#include "ofxGui.h"
#include "Arena.h"

#pragma once

namespace Box2dArena {

class TargetCanon {
public:
	TargetCanon();
	virtual ~TargetCanon();

	void setup(Arena * arena);

	void debugDraw();

	void shootNextTarget();

	ofxPanel gui;
	ofPoint center;

protected:
	Arena * arenaPtr;

	void setupGui();
	ofxFloatSlider density, bounce, friction;
	ofxFloatSlider centerOffX, centerOffY;
	ofxFloatSlider radius, minAngle, maxAngle;
	ofxFloatSlider attractionAmt;
};

} /* namespace Box2dArena */
