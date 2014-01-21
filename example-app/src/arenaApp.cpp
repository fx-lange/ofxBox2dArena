#include "arenaApp.h"

bool bDrawGui = true;
bool bDrawDebug = true;
bool bDrawWinnerPictureDebug = false;
bool bNoPlayer = true;

bool eNextTarget = true;

float scale = 1.f;
int modeToShow = 0;

//--------------------------------------------------------------
void arenaApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();

	arena.setup();
	arena.loadBackground("arena_wall.png");
	canon.setup(&arena);
	game.setup(&canon,&player,"GovtAgentBB.ttf");
	player.setup(&arena,game.getScore());
}

//--------------------------------------------------------------
void arenaApp::update() {
	if (eNextTarget) {
		eNextTarget = false;
		canon.shootNextTarget();
	}

	game.update();
	arena.update(game.getScore());
	bool action = player.update();
	if(game.isWaitingForAction() && action){
		game.andAction();
	}
}

//--------------------------------------------------------------
void arenaApp::draw() {
	ofPushStyle();
	ofPushMatrix();

	//TODO move camera instead of scaling everything!
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	ofScale(scale, scale);
	ofTranslate(-ofGetWidth() / 2.f, -ofGetHeight() / 2.f);

	if(game.isInGameMode()){
		arena.draw();
		if(!bNoPlayer)
		player.draw(bDrawDebug);
	}
	game.draw();

	if (bDrawDebug) {
		arena.drawDebug();
		canon.drawDebug(modeToShow);
		player.drawDebug();
	}

	if(bDrawWinnerPictureDebug){
		game.drawPicture(true);
	}

	ofPopMatrix();
	ofPopStyle();

	ofPushStyle();
	if (bDrawGui) {
		ofSetColor(255);
		ofSetRectMode(OF_RECTMODE_CORNER);
		arena.gui.draw();
		canon.drawGui(modeToShow);
		player.drawGui();
		game.gui.draw();
	}
	if (bDrawDebug) {
		string msg = "";
		msg += "targets: " + ofToString(arena.targetCount());
		msg += "\nfps: " + ofToString(ofGetFrameRate());
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(msg, 50, 50);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void arenaApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_RETURN:
//		game.pauseGame(false);
		game.andAction();
		bNoPlayer = false;
		break;
	case 'q':
		player.changeKinectAngle(1);
		break;
	case 'a':
		player.changeKinectAngle(-1);
		break;
	case 'd':
		bDrawDebug = !bDrawDebug;
		break;
	case 'w':
		bDrawWinnerPictureDebug = !bDrawWinnerPictureDebug;
		break;
	case 'g':
		bDrawGui = !bDrawGui;
		break;
	case '+':
		scale *= 1.5f;
		break;
	case '-':
		scale /= 1.5f;
		break;
	case OF_KEY_LEFT:
		modeToShow--;
		modeToShow = modeToShow < 0 ? 0 : modeToShow;
		break;
	case OF_KEY_RIGHT:
		modeToShow++;
		modeToShow = modeToShow > 2 ? 2 : modeToShow;
		break;
	case 'n':
	default:
		eNextTarget = true;
		break;
	}
}

//--------------------------------------------------------------
void arenaApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void arenaApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void arenaApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void arenaApp::mousePressed(int x, int y, int button) {
	ofPushStyle();
	ofSetColor(255,0,0);
	ofFill();
	ofCircle(x,y,50);
	ofPopStyle();
}

//--------------------------------------------------------------
void arenaApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void arenaApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void arenaApp::exit() {

}
