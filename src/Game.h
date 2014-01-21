#include "ofxGui.h"
#include "Score.h"
#include "TargetCanon.h"
#include "ofxTimer.h"

#pragma once

namespace Box2dArena {

class Player;

enum GameMode{
	GAME,
	PICTURE,
	HIGHSCORE
};

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon, Player * player, string fontName);
	void update();
	void draw();
	void drawPicture(bool debug = false);

	void gameDone(ofEventArgs & e);
	void pauseGame(bool pause);

	Score * getScore();

	ofxPanel gui;

private:
	void setupGui();

	Score score;
	TargetCanon * canonPtr;
	Player * playerPtr;

	ofxFloatSlider targetsPerSec, targetsPerSec2, targetsPerSec3;
	vector<ofxFloatSlider*> TPSs;
	ofxFloatSlider scoreX, scoreY, timeX;
	ofxFloatSlider hitPointDuration, scoreDrifting;

	float targetsToShoot;
	long tLastUpdate;

	ofTrueTypeFont timeRemainingFont;
	ofxTimer gameTime;
	bool bPause;
	float totalTime;
	int mode;

	GameMode gamemode;

	ofxPanel highscorePanel;
	ofxFloatSlider templateX,templateY,templateScale, templateOpacity;
	ofxFloatSlider winnerImgX, winnerImgY, winnerImgScale;
	ofxFloatSlider frameX, frameY, frameW, frameH;

	ofImage templateImg;
};

} /* namespace Box2dArena */
