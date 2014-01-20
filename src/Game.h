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

	Score score;
	TargetCanon * canonPtr;

	ofxFloatSlider targetsPerSec, scoreX, scoreY, timeX;
	ofxFloatSlider hitPointDuration, scoreDrifting;

	float targetsToShoot;
	long tLastUpdate;

	ofTrueTypeFont timeRemainingFont;
	int timeRemaingSec;
};

} /* namespace Box2dArena */
