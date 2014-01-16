#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

#pragma once

namespace Box2dArena {

class Player {
public:
	Player();
	virtual ~Player();

	void setup();
	void setupGui();
	void update();

	void draw();
	void drawDebug();

	ofxPanel gui;
private:

	void updateKinect();
	void drawContour();

	ofxKinect kinect;
	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage grayImg;
	ofxCvGrayscaleImage binaryImg;
	ofxCvGrayscaleImage grayThreshNear;
	ofxCvGrayscaleImage grayThreshFar;

	float kinectAngle;
	ofxFloatSlider nearThreshold, farThreshold;
	ofxFloatSlider opacity;

	ofxFloatSlider posX, posY, width, height;
	ofxToggle flip;

	ofxCvContourFinder contourFinder;
};

} /* namespace Box2dArena */
