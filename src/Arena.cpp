#include "Arena.h"

namespace Box2dArena {

Arena::Arena() {
}

Arena::~Arena() {
}

void Arena::setup() {
	box2d.init();
	box2d.setGravity(0, 1);
	box2d.setFPS(30.0);

	setupGui();
}

void Arena::setupGui() {
	gui.setup("arena", "arena.xml", 300, 50);
	gui.add(gravity.setup("gravity", 1, 0, 5));
	gui.add(offsetX.setup("bg offset X", 0, -500, 500));
	gui.add(offsetY.setup("bg offset Y", 0, -500, 500));
	gui.add(scale.setup("bg scale", 1, 0, 2));
	gui.loadFromFile("arena.xml");
}

void Arena::update() {
	box2d.setGravity(0, gravity); //TODO every frame?!
	box2d.update();
}

void Arena::draw() {
	ofPushStyle();
	ofSetColor(255);

	//background
	ofPushMatrix();
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(ofGetWidth() / 2.f + offsetX, ofGetHeight() / 2.f + offsetY);
	ofScale(scale, scale);
	background.draw(0, 0);
	ofPopStyle();
	ofPopMatrix();

	//targets
	for (int i = 0; i < (int) targets.size(); i++) {
		targets[i]->draw();
	}

	ofPopStyle();
}

void Arena::loadBackground(string filename) {
	background.loadImage(filename);
}

ofxBox2d & Arena::getBox2d() {
	return box2d;
}

} /* namespace Box2dArena */
