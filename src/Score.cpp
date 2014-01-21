#include "Score.h"

namespace Box2dArena {

Score::Score() :
		total(0), bCount(false) {
}

Score::~Score() {
}

void Score::setup(string fontName) {
	font.loadFont(fontName, 30, true, true, false);
	hitFont.loadFont(fontName, 55, true, true, false);
}

void Score::update(float hpDuration, float drifting) {
	long tNow = ofGetElapsedTimeMillis();
	list<HitPoint>::iterator it = hitPoints.begin();
	while (it != hitPoints.end()) {
		HitPoint & hp = *it;
		if (tNow - hp.timestamp > hpDuration * 1000.f) {
			it = hitPoints.erase(it);
		} else {
			it->pos.y -= drifting;
			++it;
		}
	}
}

void Score::draw(float x, float y) {
	ofPushStyle();
	ofSetColor(220, 27, 42);
	font.drawString(ofToString(total), x, y);
	ofSetColor(245, 191, 42);
	font.drawString(ofToString(total), x-3, y-2);
	list<HitPoint>::iterator it = hitPoints.begin();
	for (; it != hitPoints.end(); it++) {
		ofSetColor(220, 27, 42);
		hitFont.drawString("+"+ofToString(HIT), (*it).pos.x, (*it).pos.y);
		ofSetColor(245, 191, 42);
		hitFont.drawString("+"+ofToString(HIT), (*it).pos.x - 5, (*it).pos.y - 4);
	}
	ofPopStyle();
}

void Score::addHit(ofVec2f pos) {
	if (!bCount)
		return;
	total += HIT;
	hitPoints.push_back(HitPoint(pos, ofGetElapsedTimeMillis()));
}

void Score::addFail(ofVec2f pos) {
	if (!bCount)
		return;
	total -= FAIL;
	total = total < 0 ? 0 : total;
}

int Score::getTotal() {
	return total;
}

void Score::stopCounting(bool stopCounting) {
	bCount = !stopCounting;
	if (bCount == true) {
		total = 0;
	}
}

} /* namespace Box2dArena */
