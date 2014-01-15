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

	setupGui();
}

void TargetCanon::setupGui() {
	gui.setup("canon", "arena.xml", 600, 50);
	gui.add(density.setup("density", 3, 0, 5));
	gui.add(bounce.setup("bounce", 0.53, 0, 2));
	gui.add(friction.setup("friction", 0.9, 0, 5));
	gui.add(radius.setup("radius", 500, 100, 5000));
	gui.add(minAngle.setup("min angle", 0, 0, 360));
	gui.add(maxAngle.setup("max angle", 360, 0, 360));
	gui.add(centerOffX.setup("offset X", 0, -500, 500));
	gui.add(centerOffY.setup("offset Y", 0, -500, 500));
	gui.add(attractionAmt.setup("attraction amount", 10, 0, 50));
	gui.add(randomX.setup("random min", 50, 0, 400));
	gui.add(randomY.setup("random max", 50, 0, 400));
	gui.loadFromFile("arena.xml");
}

void TargetCanon::debugDraw() {
	ofPoint center(ofGetWidth() / 2.f, ofGetHeight() / 2.f);

	ofPushStyle();
	ofSetColor(0, 0, 255);
	for (int angle = minAngle; angle < maxAngle; angle += 10) {
		float x = center.x + centerOffX + radius * cos(ofDegToRad(angle + 90));
		float y = center.y + centerOffY + radius * sin(ofDegToRad(angle + 90));
		ofEllipse(x, y, 10, 10);
	}
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofNoFill();
	ofRect(center.x + centerOffX,center.y + centerOffY,randomX*2,randomY*2);
	ofPushStyle();

}

void TargetCanon::shootNextTarget() {
	ofPoint center(ofGetWidth() / 2.f, ofGetHeight() / 2.f);

	Target * target = new Target();

	float angle = 90 + ofRandom(minAngle, maxAngle);
	float tx = center.x + centerOffX + radius * cos(ofDegToRad(angle));
	float ty = center.y + centerOffY + radius * sin(ofDegToRad(angle));

	target->setPhysics(density, bounce, friction);
	target->setup(arenaPtr->getBox2d().getWorld(), tx, ty); //TODO use type instead of w,h

	float atx = center.x + centerOffX + ofRandom(-randomX,randomX);
	float aty = center.y + centerOffY + ofRandom(-randomY,randomY);

	target->addAttractionPoint(atx, aty, attractionAmt); //TODO impulse instead of force?
	//TODO rotation
	//TODO density to size factor

	arenaPtr->addTarget(target);
}

} /* namespace Box2dArena */
