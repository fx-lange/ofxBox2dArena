#include "Game.h"
#include "Player.h"

namespace Box2dArena {

Game::Game() :
		canonPtr(NULL), playerPtr(NULL), targetsToShoot(0), tLastUpdate(-1), bPause(
				true), totalTime(3), totalPoints(0), mode(0), gamemode(GAME), eTakePicture(
				false), pictureCount(0) {
}

Game::~Game() {
	gameTime.stopTimer();
	pictureTimer.stopTimer();
}

void Game::setup(TargetCanon * canon, Player * player, string fontName) {
	canonPtr = canon;
	playerPtr = player;
	score.setup(fontName);

	timeRemainingFont.loadFont(fontName, 30, true, true);
	totalPointsFont.loadFont(fontName, 50, true, true);
	highscoreFont.loadFont(fontName, 40, true, true);

	gameTime.setup(totalTime * 1000, false);
	gameTime.stopTimer();
	ofAddListener(gameTime.TIMER_REACHED, this, &Game::gameDone);

	templateImg.loadImage("templateImg.png");
	pictureTimer.setup(5 * 1000, false);
	pictureTimer.stopTimer();
	ofAddListener(pictureTimer.TIMER_REACHED, this, &Game::eventTakePicture);
	winnerImg.allocate(frameW, frameH, OF_IMAGE_COLOR);

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
	gui.add(targetsPerSec2.setup("targets per sec 2", 1, 0, 15));
	gui.add(targetsPerSec3.setup("targets per sec 3", 1, 0, 15));
	highscorePanel.setup("highscore");
	highscorePanel.add(templateX.setup("template X", 0, 0, 1500));
	highscorePanel.add(templateY.setup("template Y", 0, 0, 1500));
	highscorePanel.add(templateScale.setup("template scale", 1, 0, 2));
	highscorePanel.add(templateOpacity.setup("template opacity", 100, 0, 255));
	highscorePanel.add(winnerImgX.setup("winnerImg X", 0, 0, 1500));
	highscorePanel.add(winnerImgY.setup("winnerImg Y", 0, 0, 1500));
	highscorePanel.add(winnerImgScale.setup("winnerImg scale", 1, 0, 2));
	highscorePanel.add(frameX.setup("frame X", 0, -500, 500));
	highscorePanel.add(frameY.setup("frame Y", 0, -500, 500));
	highscorePanel.add(frameW.setup("frame W", 500, 0, 2000));
	highscorePanel.add(frameH.setup("frame H", 500, 0, 2000));
	highscorePanel.add(totalPointsX.setup("points X", 500, 0, 2000));
	highscorePanel.add(totalPointsY.setup("points Y", 500, 0, 2000));
	highscorePanel.add(highScoreLineH.setup("hs line height",100,1,250));
	gui.add(&highscorePanel);
	gui.loadFromFile("arena.xml");

	TPSs.push_back(&targetsPerSec);
	TPSs.push_back(&targetsPerSec2);
	TPSs.push_back(&targetsPerSec3);
}

void Game::update() {
	if (bPause) {
		if (eTakePicture) {
			eTakePicture = false;
			takePicture();
			gamemode = HIGHSCORE;
		}
		return;
	}

	float timeLeft = gameTime.getTimeLeftInSeconds();
	if (floor((totalTime - timeLeft) / (totalTime / 3)) > mode) {
		mode++;
		if (mode < 3) {
			canonPtr->nextMode();
		}
	}

	// ---- new targets -----
	long tNow = ofGetElapsedTimeMillis();

	if (tLastUpdate < 0) {
		tLastUpdate = tNow;
	}

	targetsToShoot += (tNow - tLastUpdate) / 1000.f * *(TPSs[mode]);

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
	totalPoints = score.getTotal();
	pauseGame(true);
	cout << "TOTAL: " << totalPoints << endl;
	gamemode = PICTURE;
	pictureTimer.startTimer();
}

void Game::eventTakePicture(ofEventArgs & e) {
	eTakePicture = true;
	pictureTimer.reset();
	pictureTimer.pauseTimer();
}

void Game::takePicture() {
	ofxCvColorImage & colorImg = playerPtr->getColorImg();
	colorImg.setROI(frameX, frameY, frameW, frameH);
	winnerImg.setFromPixels(colorImg.getRoiPixelsRef());
	colorImg.resetROI();
	string filename = ofToString(++pictureCount) + "_" + ofToString(totalPoints)
			+ ".png";
	winnerImg.saveImage("highscores/" + filename);
	highscores.push_back(HighScore(totalPoints, winnerImg));
}

void Game::draw() {
	switch ((int) gamemode) {
	case GAME: {
		score.draw(scoreX, scoreY);

		int timeRemaingSec = gameTime.getTimeLeftInSeconds();
		int sec = timeRemaingSec % 60;
		int min = floor(timeRemaingSec / 60.f);

		string timeStr = ofToString(min, 0, 2, '0') + ":"
				+ ofToString(sec, 0, 2, '0');
		timeRemainingFont.drawString(timeStr, timeX, scoreY);
		break;
	}
	case PICTURE:
		drawPicture();
		break;
	case HIGHSCORE:
		drawHighscores();
		break;
	}
}

void Game::drawPicture(bool debug) {
	ofxCvColorImage & colorImg = playerPtr->getColorImg();

	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(winnerImgX, winnerImgY);
	ofScale(winnerImgScale, winnerImgScale);
	colorImg.draw(0, 0);
	ofPopMatrix();

	ofSetColor(255, 255, 255, templateOpacity);
	ofPushMatrix();
	ofTranslate(templateX, templateY);
	ofScale(templateScale, templateScale);
	templateImg.draw(0, 0);
	ofPopMatrix();

	ofSetColor(0);
	string scoreStr = ofToString(totalPoints) + " (#01)";
	ofRectangle rect = totalPointsFont.getStringBoundingBox(scoreStr, 0, 0);
	totalPointsFont.drawString(scoreStr, totalPointsX - rect.width / 2.f,
			totalPointsY);

	if (debug) {
		ofSetColor(255, 0, 0);
		ofPushMatrix();
		ofTranslate(winnerImgX, winnerImgY);
		ofRect(frameX, frameY, frameW, frameH);
		ofPopMatrix();
	}
	ofPopStyle();
}

void Game::drawHighscores(){
	//TODO draw headliner image
	ofSetColor(255);
	list<HighScore>::iterator it = highscores.begin();
	int i = 0;
	for(;it!=highscores.end();++it,++i){
		ofPushMatrix();
		ofTranslate(0,highScoreLineH*i);
		ofPushMatrix();
		float scale = highScoreLineH / it->image.height;
		ofScale(scale,scale);
		it->image.draw(0,0);
		ofPopMatrix();
		ofSetColor(220, 27, 42);
		highscoreFont.drawString(ofToString(it->points),it->image.width * scale + 42,0);
		ofSetColor(245, 191, 42);
		highscoreFont.drawString(ofToString(it->points),it->image.width * scale + 40,-2);
		ofPopMatrix();
	}
}

void Game::pauseGame(bool pause) {
	score.stopCounting(pause);
	if (pause == false) {
		mode = 0;
		canonPtr->resetMode();
		//TODO use restart COUNTDOWN here instead!
		gameTime.reset();
		gameTime.startTimer();
		tLastUpdate = -1;
	}
	bPause = pause;
}

Score * Game::getScore() {
	return &score;
}

} /* namespace Box2dArena */
