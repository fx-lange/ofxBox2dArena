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

protected:
	Arena * arenaPtr;

	void setupGui();
	ofxFloatSlider density, bounce, friction;
	ofxFloatSlider centerOffX, centerOffY;
	ofxFloatSlider radius, minAngle, maxAngle;
	ofxFloatSlider attractionAmt, angularVel, randomX,randomY;
};

} /* namespace Box2dArena */