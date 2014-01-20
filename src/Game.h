#include "ofxGui.h"
#include "Score.h"
#include "TargetCanon.h"
#include "ofxTimer.h"

#pragma once

namespace Box2dArena {

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon, string fontName);
	void update();
	void draw();

	void gameDone(ofEventArgs & e);
	void pauseGame(bool pause);

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
	ofxTimer gameTime;
	bool bPause;
};

} /* namespace Box2dArena */
