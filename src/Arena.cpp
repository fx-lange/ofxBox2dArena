#include "Arena.h"
#include "Score.h"

namespace Box2dArena {

Arena::Arena() {
}

Arena::~Arena() {
}

void Arena::setup() {
	box2d.init();
	box2d.setGravity(0, 1);
	box2d.setFPS(30.0);

	setupGui();
}

void Arena::setupGui() {
	gui.setup("arena", "arena.xml", 250, 60);
	gui.add(width.setup("arena width", 800, 800, 1600));
	gui.add(height.setup("arena height", 600, 600, 900));
	gui.add(destroyLevel.setup("destroy level", 1000, 500, 2000));
	gui.add(gravity.setup("gravity", 1, 0, 5));
	gui.add(offsetX.setup("bg offset X", 0, -500, 500));
	gui.add(offsetY.setup("bg offset Y", 0, -500, 500));
	gui.add(scale.setup("bg scale", 1, 0, 2));
	gui.loadFromFile("arena.xml");
}

void Arena::update(Score * score) {
	updateTargets(score);

	box2d.setGravity(0, gravity); //TODO every frame?!
	box2d.update();
}

void Arena::updateTargets(Score * score) {
	list<Target*>::iterator it = targets.begin();
	for (; it != targets.end();) {
		Target * target = *it;
		float x = target->getPosition().x;
		float y = target->getPosition().y;

		if (isInside(x, y)) {
			if (!target->bEnteredArena) {
				//is entering arena
				target->bEnteredArena = true;
				target->color.set(0, 255, 0);
			}
		} else {
			if (target->bEnteredArena) {
				//is leaving arena
				if (!target->bHit && !target->bMissed) {
					target->color.set(255, 0, 0);
					target->bMissed = true;
					score->addFail(target->getPosition());
				}
			}

			if (y > destroyLevel) {
				it = targets.erase(it);
				delete target;
				continue;
			}
		}
		++it;
	}
}

void Arena::drawTargets() {
	ofPushStyle();
	ofSetColor(255);

	//targets
	list<Target*>::iterator it = targets.begin();
	for (; it != targets.end(); it++) {
		Target * target = *it;
		target->draw();
	}

	ofPopStyle();
}

void Arena::drawBg(){
	ofPushStyle();
	ofSetColor(255);

	//background
	ofPushMatrix();
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(ofGetWidth() / 2.f + offsetX, ofGetHeight() / 2.f + offsetY);
	ofScale(scale, scale);
	background.draw(0, 0);
	ofPopStyle();
	ofPopMatrix();
	ofPopStyle();
}

void Arena::drawDebug() {
	ofPushMatrix();
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofNoFill();
	ofTranslate(ofGetWidth() / 2.f, ofGetHeight() / 2.f);
	ofSetColor(255, 0, 0);
	ofRect(0, 0, width, height);
	ofTranslate(0, -ofGetHeight() / 2.f);
	ofLine(-width / 2.f, destroyLevel, width / 2.f, destroyLevel);
	ofPopStyle();
	ofPopMatrix();
}

bool Arena::isInside(float x, float y) {
	if (abs(x - ofGetWidth() * 0.5f) < width / 2.f
			&& abs(y - ofGetHeight() * 0.5f) < height / 2.f) {
		return true;
	} else {
		return false;
	}
}

void Arena::addTarget(Target * target) {
	targets.push_back(target);
}

list<Target*> & Arena::getTargets() {
	return targets;
}

int Arena::targetCount() {
	return (int) targets.size();
}

void Arena::loadBackground(string filename) {
	background.loadImage(filename);
}

ofxBox2d & Arena::getBox2d() {
	return box2d;
}

} /* namespace Box2dArena */
