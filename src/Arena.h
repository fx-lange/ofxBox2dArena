#include "ofxBox2d.h"
#include "ofxGui.h"
#include "Target.h"

#pragma once

namespace Box2dArena {

class Score;

class Arena {
public:
	Arena();
	virtual ~Arena();

	void setup();
	void update(Score * score);
	void drawTargets();
	void drawBg();
	void drawDebug();

	void loadBackground(string filename);

	void addTarget(Target * target);
	list<Target*> & getTargets();
	int targetCount();

	ofxBox2d & getBox2d();

	ofxPanel gui;

private:
	ofxBox2d box2d;
	list<Target*> targets;

	void updateTargets(Score * score);
	bool isInside(float x, float y);

	ofImage background;

	void setupGui();
	ofxFloatSlider gravity;
	ofxFloatSlider offsetX, offsetY, scale;
	ofxIntSlider width, height, destroyLevel;
};

} /* namespace Box2dArena */
