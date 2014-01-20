#include "ofxGui.h"
#include "Score.h"
#include "TargetCanon.h"

#pragma once

namespace Box2dArena {

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon);
	void update();
	void draw();

	Score * getScore();

	ofxPanel gui;

private:
	void setupGui();

	ofxFloatSlider targetsPerSec, scoreX, scoreY;
	float targetsToShoot;
	long tLastUpdate;

	TargetCanon * canonPtr;
	Score score;
};

} /* namespace Box2dArena */
