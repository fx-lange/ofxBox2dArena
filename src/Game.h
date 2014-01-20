#include "ofxGui.h"
#include "Score.h"
#include "TargetCanon.h"

#pragma once

namespace Box2dArena {

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon, string fontName);
	void update();
	void draw();

	Score * getScore();

	ofxPanel gui;

private:
	void setupGui();

	TargetCanon * canonPtr;
	ofxFloatSlider targetsPerSec, scoreX, scoreY;
	float targetsToShoot;
	long tLastUpdate;

	Score score;
};

} /* namespace Box2dArena */
