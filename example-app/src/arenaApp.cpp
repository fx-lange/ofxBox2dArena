#include "arenaApp.h"

bool bDrawGui = true;
bool bDrawDebug = true;

bool eNextTarget = false;

float scale = 1.f;

//--------------------------------------------------------------
void arenaApp::setup() {
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableAntiAliasing();

	arena.setup();
	arena.loadBackground("wall.jpg");
	canon.setup(&arena);
}

//--------------------------------------------------------------
void arenaApp::update() {
	if (eNextTarget) {
		eNextTarget = false;
		canon.shootNextTarget();
	}

	arena.update();
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
	if (bDrawDebug) {
		arena.drawDebug();
		canon.debugDraw();
	}

	ofPopMatrix();
	ofPopStyle();

	ofPushStyle();
	if (bDrawGui) {
		ofSetColor(255);
		arena.gui.draw();
		canon.gui.draw();
	}
	if (bDrawDebug) {
		string msg = "";
		msg += "targets: " + ofToString(arena.targetCount());
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(msg, 50, 50);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void arenaApp::keyPressed(int key) {
	switch (key) {
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