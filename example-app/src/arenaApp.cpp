#include "arenaApp.h"

bool bDrawGui = true;

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

	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	ofScale(scale, scale);
	ofTranslate(-ofGetWidth() / 2.f, -ofGetHeight() / 2.f);

	arena.draw();
	canon.debugDraw();

	ofPopMatrix();
	ofPopStyle();

	if (bDrawGui) {
		ofSetColor(255);
		arena.gui.draw();
		canon.gui.draw();
	}
}

//--------------------------------------------------------------
void arenaApp::keyPressed(int key) {
	switch (key) {
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
