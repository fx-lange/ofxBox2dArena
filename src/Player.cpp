#include "Player.h"
#include "Score.h"

namespace Box2dArena {

Player::Player() :
		kinectAngle(0), arenaPtr(NULL), motion(NULL), scorePtr(NULL) {
}

Player::~Player() {
}

void Player::setup(Arena * arena, Score * score) {
	arenaPtr = arena;
	scorePtr = score;

	kinect.setRegistration(true);
	kinect.init();
	kinect.open();

	kinectAngle = 0;

	motion = new ofxCvMotionTemplates(kinect.width, kinect.height);
	motion->setup();
	motion->gui.setPosition(60, 400);

	colorImg.allocate(kinect.width, kinect.height);
	binaryImg.allocate(kinect.width, kinect.height);
	grayImg.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	motionImg.allocate(kinect.width, kinect.height);
	silhouettesImg.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);

	setupGui();
	kinect.setCameraTiltAngle(kinectAngle);
}

void Player::setupGui() {
	gui.setup("player", "arena.xml", 50, 60);
	gui.add(bFlip.setup("flip src", false));
	contour.setup("contour");
	contour.add(kinectAngle.setup("kinect tilt", 0, -30, 30));
	contour.add(nearThreshold.setup("kinect near", 0, 0, 255));
	contour.add(farThreshold.setup("kinect far", 0, 0, 255));
	contour.add(opacity.setup("opacity", 0, 0, 255));
	contour.add(stepSize.setup("step size", 3, 1, 10));
	contour.add(simplify.setup("simplify", 1, 0.001, 20));
	contour.add(bDrawCurved.setup("curved vertex", false));
	contour.add(posX.setup("pos x", 0, -1000, 1000));
	contour.add(posY.setup("pos y", 0, -1000, 1000));
	contour.add(width.setup("width", 800, 0, 2000));
	contour.add(height.setup("height", 600, 0, 2000));
	gui.add(&contour);
	motionPanel.setup("motion");
	motionPanel.add(testForce.setup("test force", 10, 0, 1000));
	motionPanel.add(minDistance.setup("min distance", 100, 5, 400));
	gui.add(&motionPanel);
	gui.loadFromFile("arena.xml");
}

bool Player::update() {

	bool action = updateKinect();
	updateForces();
	return action;
}

bool Player::updateKinect() {
	bool action = false;
	kinect.update();

	if (kinect.isFrameNew()) {

		grayImg.setFromPixels(kinect.getDepthPixels(), kinect.width,
				kinect.height);
		if (bFlip) {
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
		//TODO /erode derode?!

		contourFinder.findContours(binaryImg, 10,
				(kinect.width * kinect.height) / 2, 20, true, true);//TODO GUI
		//TODO holes! learning opencv page 237! use different sorting and find way to draw poly with hole
		//http://forum.openframeworks.cc/t/circles-with-holes-or-with-stroke/8173/3
		if(contourFinder.nBlobs>0){
			action = true;
		}
	}
	return action;
}

void Player::updateForces() {
	motionImg = motion->calculateMotions(binaryImg);
	silhouettesImg.setFromPixels(motionImg.getPixels(), kinect.width,
			kinect.height, OF_IMAGE_GRAYSCALE);
	silhouettesImg.setImageType(OF_IMAGE_COLOR_ALPHA);
	motion->setBlackToTransparent(silhouettesImg);

	list<Target*> & targets = arenaPtr->getTargets();
	list<Target*>::iterator it = targets.begin();

	if (ofGetMousePressed()) {
		ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
		for (; it != targets.end(); ++it) {
			float dis = mouse.distance((*it)->getPosition());
			if (dis < minDistance) {
				(*it)->addRepulsionForce(mouse, testForce);
				(*it)->bHit = true;
			}
		}
	}

	vector<ofxCvMotionBlob> & motions = motion->getLocalMotions();
	for (int i = 0; i < (int) motions.size(); i++) {

		ofPoint mp = motions[i].centroid;
		mp.x *= width / kinect.width;
		mp.y *= height / kinect.height;
		mp.x += posX;
		mp.y += posY;
//		float area = motions[i].area;
//		float count = motions[i].count;
//		cout << "c: " << count << " a: " << area << " c/a: " << count / area
//				<< endl;

		for (it = targets.begin(); it != targets.end(); ++it) {
			Target * t = *it;
			ofVec2f tPos = t->getPosition();
			if (abs(tPos.x - mp.x) < motions[i].boundingRect.width + minDistance
					&& abs(tPos.y - mp.y)
							< motions[i].boundingRect.height + minDistance) {
//			float dis = mp.distance(tPos);
//			if (dis < minDistance) {
				t->addRepulsionForce(mp, testForce);
//				t->addForce(motions[i].forceDir.getNormalized(),testForce);
//				t->addImpulseForce(motions[i].forceDir,ofVec2f(testForce,testForce));
				if (!t->bHit) {
					t->bHit = true;
					scorePtr->addHit(t->getPosition());
				}
			}
		}
	}
}

void Player::draw(bool debug) {
	drawContour(debug);
}

void Player::drawContour(bool debug) {
	ofPushStyle();
	ofEnableAlphaBlending();
	ofFill();

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

	ofPolyline line;
	for (int i = 0; i < (int) contourFinder.blobs.size(); i++) { //TODO smoothing!
		ofxCvBlob & blob = contourFinder.blobs[i];
		line.clear();
		line.addVertices(blob.pts);
		line.simplify(simplify);
		if (blob.hole) {
			ofSetColor(100, 100, 100, opacity);
		} else {
			ofSetColor(0, 0, 0, opacity);
		}
		ofBeginShape();
		for (int j = 0; j < (int) line.size(); j += stepSize) {
			if (bDrawCurved) {
				ofCurveVertex(line[j].x, line[j].y);
			} else {
				ofVertex(line[j].x, line[j].y);
			}
		}
		ofEndShape(false);
	}

	ofSetColor(150, 130, 20, 70);
	ofSetRectMode(OF_RECTMODE_CORNER);
	silhouettesImg.draw(0, 0);

	if (debug) {
		ofSetColor(255, 255, 255);
		vector<ofxCvMotionBlob> & motions = motion->getLocalMotions();
		for (int i = 0; i < (int) motions.size(); i++) {
			motions[i].draw(0, 0);
		}
	}
	ofPopMatrix();

	ofPopStyle();
}

void Player::drawDebug() {
	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 50);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	binaryImg.draw(0, 0);
	motionImg.draw(0, 0);
	ofPopMatrix();
	ofPopStyle();
}

void Player::drawGui() {
	gui.draw();
	motion->gui.draw();
}

ofxCvColorImage & Player::getColorImg() {
	colorImg.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
	if (bFlip) {
		cvFlip(colorImg.getCvImage(), colorImg.getCvImage(), 1);
		colorImg.flagImageChanged();
	}
	return colorImg;
}

void Player::changeKinectAngle(int diff) {
	kinectAngle = kinectAngle + diff;
	kinect.setCameraTiltAngle(kinectAngle);
}

} /* namespace Box2dArena */
