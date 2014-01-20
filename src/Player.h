#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxCvMotionTemplates.h"
#include "Arena.h"

#pragma once

namespace Box2dArena {

class Score;

class Player {
public:
	Player();
	virtual ~Player();

	void setup(Arena * arena, Score * score);
	void setupGui();
	void update();

	void draw(bool debug = false);
	void drawDebug();
	void drawGui();

	void changeKinectAngle(int diff);

private:
	void updateKinect();
	void updateForces();
	void drawContour(bool debug);

	// --- kinect visualization
	ofxKinect kinect;
	ofxCvContourFinder contourFinder;
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImg;
	ofxCvGrayscaleImage binaryImg;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar;

	ofxPanel gui, contour, motionPanel;
	ofxFloatSlider kinectAngle;
	ofxFloatSlider nearThreshold, farThreshold;
	ofxFloatSlider opacity, simplify;
	ofxIntSlider stepSize;
	ofxToggle bFlip, bDrawCurved;
	ofxFloatSlider posX, posY, width, height;

	// --- forces ---
	Arena * arenaPtr;
	ofxFloatSlider testForce, minDistance;

	// --- motion ---
	ofxCvMotionTemplates * motion;
	ofxCvGrayscaleImage motionImg;
	ofImage silhouettesImg;

	// --- game ---
	Score * scorePtr;
};

} /* namespace Box2dArena */
