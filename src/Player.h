#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "Arena.h"

#pragma once

namespace Box2dArena {

class Player {
public:
	Player();
	virtual ~Player();

	void setup(Arena * arena);
	void setupGui();
	void update();

	void draw();
	void drawDebug();

	void changeKinectAngle(int diff);

	ofxPanel gui;
private:
	void updateKinect();
	void updateForces();
	void drawContour();

	// --- kinect visualization
	ofxKinect kinect;
	ofxCvContourFinder contourFinder;
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImg;
	ofxCvGrayscaleImage binaryImg;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar;

	ofxFloatSlider kinectAngle;
	ofxFloatSlider nearThreshold, farThreshold;
	ofxFloatSlider opacity, simplify;
	ofxIntSlider stepSize;
	ofxToggle bFlip, bDrawCurved;
	ofxFloatSlider posX, posY, width, height;

	// --- forces

	Arena * arenaPtr;
	ofxFloatSlider testForce;
};

} /* namespace Box2dArena */
