#include "Player.h"

namespace Box2dArena {

Player::Player() :
		kinectAngle(0), arenaPtr(NULL) {
}

Player::~Player() {
}

void Player::setup(Arena * arena) {
	arenaPtr = arena;

	kinect.setRegistration(true);
	kinect.init();
	kinect.open();

	kinectAngle = 0;
	kinect.setCameraTiltAngle(kinectAngle);

	colorImg.allocate(kinect.width, kinect.height);
	binaryImg.allocate(kinect.width, kinect.height);
	grayImg.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	setupGui();
}

void Player::setupGui() {
	gui.setup("player", "arena.xml", 100, 50);
	gui.add(nearThreshold.setup("kinect near", 0, 0, 255));
	gui.add(farThreshold.setup("kinect far", 0, 0, 255));
	gui.add(opacity.setup("opacity", 0, 0, 255));
	gui.add(stepSize.setup("step size", 3, 1, 10));
	gui.add(flip.setup("flip src"));
	gui.add(posX.setup("pos x", 0, -1000, 1000));
	gui.add(posY.setup("pos y", 0, -1000, 1000));
	gui.add(width.setup("width", 800, 0, 2000));
	gui.add(height.setup("height", 600, 0, 2000));
	gui.loadFromFile("arena.xml");
}

void Player::update() {

	updateKinect();
	updateForces();
}

void Player::updateKinect() {
	kinect.update();

	if (kinect.isFrameNew()) {

		grayImg.setFromPixels(kinect.getDepthPixels(), kinect.width,
				kinect.height);
		if (flip) {
			cvFlip(grayImg.getCvImage(), grayImg.getCvImage(), 1);
			grayImg.flagImageChanged();
		}

		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		grayThreshNear = grayImg;
		grayThreshFar = grayImg;
		grayThreshNear.threshold(nearThreshold, true);
		grayThreshFar.threshold(farThreshold);

		cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(),
				binaryImg.getCvImage(), NULL);
		binaryImg.flagImageChanged();
		//TODO try both thresholds on binaryImg without far&near
		//TODO mirroring
		//TODO /erode derode?!

		contourFinder.findContours(binaryImg, 10,
				(kinect.width * kinect.height) / 2, 20, false);		//TODO GUI
		//TODO holes!
	}
}

void Player::updateForces() {
	list<Target*> & targets = arenaPtr->getTargets();
	list<Target*>::iterator it = targets.begin();
	if (ofGetMousePressed()) {
		ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
		for (; it != targets.end(); ++it) {
			float dis = mouse.distance((*it)->getPosition());
			if (dis < 200){
				(*it)->addRepulsionForce(mouse, 9);
				(*it)->bHit = true;
			}
		}
	}
}

void Player::draw() {
	drawContour();
}

void Player::drawContour() {
	ofPushStyle();
	ofEnableAlphaBlending();
	ofFill();
	ofSetColor(0, 0, 0, opacity);

	float cWidth = contourFinder.getWidth();
	float cHeight = contourFinder.getHeight();
	float scalex = 1.0f, scaley = 1.0f;

	if (cWidth != 0) {
		scalex = width / cWidth;
	}
	if (cHeight != 0) {
		scaley = height / cHeight;
	}

	ofPushMatrix();
	ofTranslate(posX, posY);
	ofScale(scalex, scaley, 0.0);

	for (int i = 0; i < (int) contourFinder.blobs.size(); i++) { //TODO smoothing!
		ofxCvBlob & blob = contourFinder.blobs[i];
		ofBeginShape();
		for (int j = 0; j < blob.nPts; j += stepSize) {
			ofCurveVertex(blob.pts[j].x, blob.pts[j].y);
		}
		ofEndShape();
	}
	ofPopMatrix();

	ofPopStyle();
}

void Player::drawDebug() {
	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 50);
	ofSetRectMode (OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	binaryImg.draw(0, 0);
	ofPopMatrix();
	ofPopStyle();
}

void Player::changeKinectAngle(int diff) {
	kinectAngle += diff;
	kinect.setCameraTiltAngle(kinectAngle);
}

} /* namespace Box2dArena */
