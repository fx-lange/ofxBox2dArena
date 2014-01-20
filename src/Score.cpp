#include "Score.h"

namespace Box2dArena {

Score::Score() :
		total(0), bCount(false) {
}

Score::~Score() {
}

void Score::setup(string fontName) {
	font.loadFont(fontName, 30, true, true, false);
	hitFont.loadFont(fontName, 40, true, true, false);
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
	font.drawString(ofToString(total), x, y);
	list<HitPoint>::iterator it = hitPoints.begin();
	for (; it != hitPoints.end(); it++) {
		ofSetColor(255, 50, 0);
		hitFont.drawString(ofToString(HIT), (*it).pos.x, (*it).pos.y);
		ofSetColor(200, 200, 0);
		hitFont.drawString(ofToString(HIT), (*it).pos.x - 1, (*it).pos.y - 1);
	}
	ofPopStyle();
}

void Score::addHit(ofVec2f pos) {
	if(!bCount)
		return;
	total += HIT;
	hitPoints.push_back(HitPoint(pos, ofGetElapsedTimeMillis()));
}

void Score::addFail(ofVec2f pos) {
	if(!bCount)
		return;
	total -= FAIL;
	total = total < 0 ? 0 : total;
}

int Score::getTotal(){
	return total;
}

void Score::stopCounting(bool stopCounting){
	bCount = !stopCounting;
	if(bCount == true){
		total = 0;
	}
}

} /* namespace Box2dArena */
