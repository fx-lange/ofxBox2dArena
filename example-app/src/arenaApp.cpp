#include "arenaApp.h"

bool bDrawGui = true;
bool bDrawDebug = true;

bool eNextTarget = true;

float scale = 1.f;

//--------------------------------------------------------------
void arenaApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();

	arena.setup();
	arena.loadBackground("arena_wall.png");
	canon.setup(&arena);
	player.setup(&arena);
	game.setup(&canon);
}

//--------------------------------------------------------------
void arenaApp::update() {
	if (eNextTarget) {
		eNextTarget = false;
		canon.shootNextTarget();
	}

	game.update();
	arena.update();
	player.update();
}

//--------------------------------------------------------------
void arenaApp::draw() {
	ofPushStyle();
	ofPushMatrix();

	//TODO move camera instead of scaling everything!
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	ofScale(scale, scale);
	ofTranslate(-ofGetWidth() / 2.f, -ofGetHeight() / 2.f);

	arena.draw();
	player.draw();

	if (bDrawDebug) {
		arena.drawDebug();
		canon.drawDebug();
		player.drawDebug();
	}

	ofPopMatrix();
	ofPopStyle();

	ofPushStyle();
	if (bDrawGui) {
		ofSetColor(255);
		arena.gui.draw();
		canon.gui.draw();
		player.gui.draw();
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
	case 'q':
		player.changeKinectAngle(1);
		break;
	case 'a':
		player.changeKinectAngle(-1);
		break;
	case 'd':
		bDrawDebug = !bDrawDebug;
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
