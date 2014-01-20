#include "Game.h"

namespace Box2dArena {

Game::Game() :
		canonPtr(NULL), targetsToShoot(0), tLastUpdate(-1), bPause(true) {
}

Game::~Game() {
	gameTime.stopTimer();
}

void Game::setup(TargetCanon * canon, string fontName) {
	canonPtr = canon;
	score.setup(fontName);

	timeRemainingFont.loadFont(fontName, 30, true, true);

	gameTime.setup(90 * 1000, false);
	gameTime.pauseTimer();
	ofAddListener(gameTime.TIMER_REACHED, this, &Game::gameDone);

	setupGui();
}

void Game::setupGui() {
	gui.setup("game", "arena.xml", 650, 60);
	gui.add(scoreX.setup("score x", 0, -500, 500));
	gui.add(scoreY.setup("score y", 0, -500, 500));
	gui.add(timeX.setup("time x", 1000, -500, 2000));
	gui.add(hitPointDuration.setup("hp duration", 1, 0, 4));
	gui.add(scoreDrifting.setup("score drifting", 0, 0, 2));
	gui.add(targetsPerSec.setup("targets per sec", 1, 0, 15));
	gui.loadFromFile("arena.xml");
}

void Game::update() {
	if (bPause)
		return;

	// ---- new targets -----
	long tNow = ofGetElapsedTimeMillis();

	if (tLastUpdate < 0) {
		tLastUpdate = tNow;
	}

	targetsToShoot += (tNow - tLastUpdate) / 1000.f * targetsPerSec;

	int shots = floor(targetsToShoot);
	targetsToShoot -= (float) shots;
	for (int i = 0; i < shots; ++i) {
		canonPtr->shootNextTarget();
	}

	tLastUpdate = tNow;

	// ---- score ----
	score.update(hitPointDuration, scoreDrifting);
}

void Game::gameDone(ofEventArgs & e) {
	int totalPoints = score.getTotal();
	pauseGame(true);
	cout << "TOTAL: " << totalPoints << endl;
}

void Game::draw() {
	score.draw(scoreX, scoreY);

	int timeRemaingSec = gameTime.getTimeLeftInSeconds();
	int sec = timeRemaingSec % 60;
	int min = floor(timeRemaingSec / 60.f);

	string timeStr = ofToString(min, 0, 2, '0') + ":"
			+ ofToString(sec, 0, 2, '0');
	timeRemainingFont.drawString(timeStr, timeX, scoreY);
}

void Game::pauseGame(bool pause) {
	bPause = pause;
	score.stopCounting(pause);
	if (bPause == false) {
		gameTime.reset();
		tLastUpdate = -1;
	}
}

Score * Game::getScore() {
	return &score;
}

} /* namespace Box2dArena */
