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
	void drawDebug();

	void loadBackground(string filename);

	void addTarget(Target * target);
	int targetCount();

	ofxBox2d & getBox2d();

	ofxPanel gui;

private:
	ofxBox2d box2d;
	list<Target*> targets;

	void updateTargets();
	bool isInside(float x, float y);

	ofImage background;

	void setupGui();
	ofxFloatSlider gravity;
	ofxFloatSlider offsetX, offsetY, scale;
	ofxIntSlider width, height, destroyLevel;
};

} /* namespace Box2dArena */
