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

	void loadBackground(string filename);

	ofxBox2d & getBox2d();

	vector<Target*> targets;

	ofxPanel gui;

private:
	ofxBox2d box2d;

	ofImage background;

	void setupGui();
	ofxFloatSlider gravity;
	ofxFloatSlider offsetX, offsetY, scale;
};

} /* namespace Box2dArena */
