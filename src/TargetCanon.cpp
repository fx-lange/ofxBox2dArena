#include "TargetCanon.h"

#include "Target.h"

namespace Box2dArena {

TargetCanon::TargetCanon() :
		arenaPtr(NULL) {
}

TargetCanon::~TargetCanon() {
}

void TargetCanon::setup(Arena * arena) {
	arenaPtr = arena;
	center.set(ofGetWidth() / 2.f, ofGetHeight() / 2.f);

	setupGui();
}

void TargetCanon::setupGui() {
	gui.setup("canon", "arena.xml", 600, 50);
	gui.add(density.setup("density", 3, 0, 50));
	gui.add(bounce.setup("bounce", 0.53, 0, 2));
	gui.add(friction.setup("friction", 0.9, 0, 5));
	gui.add(radius.setup("radius", 500, 100, 5000));
	gui.add(minAngle.setup("min angle", 0, 0, 360));
	gui.add(maxAngle.setup("max angle", 360, 0, 360));
	gui.add(centerOffX.setup("offset X", 0, -500, 500));
	gui.add(centerOffY.setup("offset Y", 0, -500, 500));
	gui.add(attractionAmt.setup("attraction amount",10,0,50));
	gui.loadFromFile("arena.xml");
}

void TargetCanon::debugDraw() {
	ofPushStyle();
	ofSetColor(255, 0, 0);
	for (int angle = minAngle; angle < maxAngle; angle += 10) {
		float x = center.x + centerOffX
				+ radius * cos(ofDegToRad(angle + 90));
		float y = center.y + centerOffY
				+ radius * sin(ofDegToRad(angle + 90));
		ofEllipse(x, y, 10, 10);
	}
	ofPushStyle();
}

void TargetCanon::shootNextTarget() {
	Target * target = new Target();

	float angle = 90 + ofRandom(minAngle, maxAngle);
	float tx = center.x + centerOffX
			+ radius * cos(ofDegToRad(angle));
	float ty = center.y + centerOffY
			+ radius * sin(ofDegToRad(angle));

	target->setPhysics(density, bounce, friction);
	target->setup(arenaPtr->getBox2d().getWorld(), tx, ty, 30, 30); //TODO use type instead of w,h

	//TODO add toCenter force
	target->addAttractionPoint(ofPoint(center.x+centerOffX,center.y+centerOffY),
			attractionAmt); //TODO impulse instead of force?

	arenaPtr->targets.push_back(target);
}

} /* namespace Box2dArena */
