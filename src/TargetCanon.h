#include "ofxGui.h"
#include "Arena.h"

#pragma once

namespace Box2dArena {

#define NUM_MODES 3

struct ModePanel {
	ofxPanel gui;
	ofxFloatSlider density, bounce, friction;
	ofxFloatSlider centerOffX, centerOffY;
	ofxFloatSlider radius, minAngle, maxAngle;
	ofxFloatSlider attractionAmt, angularVel, randomX, randomY;

	void setupPanel(string group);
};

class TargetCanon {
public:
	TargetCanon();
	virtual ~TargetCanon();

	void setup(Arena * arena);

	void drawDebug(int modeId);
	void drawGui(int modeId);

	void shootNextTarget();
	void nextMode();
	void resetMode();

protected:
	Arena * arenaPtr;

	void setupGui();
	vector<ModePanel*> modes;
	ModePanel * mode;
	int modeIdx;
};

} /* namespace Box2dArena */
