#include "ofxBox2d.h"
#include "ofxGui.h"
#include "Target.h"

#pragma once

namespace Box2dArena {

class Arena {
public:
	Arena();
	virtual ~Arena();

	void setup();
	void update();
	void draw();

	ofxBox2d & getBox2d();

	vector<Target*> targets;

	ofxPanel gui;

private:
	ofxBox2d box2d;

	void setupGui();
	ofxFloatSlider gravity;
};

} /* namespace Box2dArena */
