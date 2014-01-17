#include "ofxGui.h"
#include "TargetCanon.h"

#pragma once

namespace Box2dArena {

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon);
	void update();

	ofxPanel gui;

private:
	void setupGui();

	ofxFloatSlider targetsPerSec;
	float targetsToShoot;
	long tLastUpdate;

	TargetCanon * canonPtr;
};

} /* namespace Box2dArena */
