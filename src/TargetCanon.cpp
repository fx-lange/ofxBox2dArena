#include "TargetCanon.h"

#include "Target.h"

namespace Box2dArena {

void ModePanel::setupPanel(string group){
	gui.setup(group, "arena.xml", 450, 60);
	gui.add(density.setup("density", 3, 0, 5));
	gui.add(bounce.setup("bounce", 0.53, 0, 2));
	gui.add(friction.setup("friction", 0.9, 0, 5));
	gui.add(radius.setup("radius", 500, 100, 5000));
	gui.add(minAngle.setup("min angle", 0, 0, 360));
	gui.add(maxAngle.setup("max angle", 360, 0, 360));
	gui.add(centerOffX.setup("offset X", 0, -500, 500));
	gui.add(centerOffY.setup("offset Y", 0, -500, 500));
	gui.add(attractionAmt.setup("attraction amount", 10, 0, 50));
	gui.add(angularVel.setup("angular vel", 1, 0, 5));
	gui.add(randomX.setup("random min", 50, 0, 400));
	gui.add(randomY.setup("random max", 50, 0, 400));
	gui.loadFromFile("arena.xml");
}

TargetCanon::TargetCanon() :
		arenaPtr(NULL),modeIdx(0),mode(NULL) {
}

TargetCanon::~TargetCanon() {
}

void TargetCanon::setup(Arena * arena) {
	arenaPtr = arena;

	setupGui();
}

void TargetCanon::setupGui() {
	ModePanel * panel = new ModePanel();
	panel->setupPanel("canon");
	modes.push_back(panel);
	panel = new ModePanel();
	panel->setupPanel("canon2");
	modes.push_back(panel);
	panel = new ModePanel();
	panel->setupPanel("canon3");
	modes.push_back(panel);
	mode = modes[0];
}

void TargetCanon::drawDebug(int modeId) {
	ofPoint center(ofGetWidth() / 2.f, ofGetHeight() / 2.f);

	ofPushStyle();
	ofSetColor(0, 0, 255);
	for (int angle = modes[modeId]->minAngle; angle < modes[modeId]->maxAngle; angle += 10) {
		float x = center.x + modes[modeId]->centerOffX + modes[modeId]->radius * cos(ofDegToRad(angle + 90));
		float y = center.y + modes[modeId]->centerOffY + modes[modeId]->radius * sin(ofDegToRad(angle + 90));
		ofEllipse(x, y, 10, 10);
	}
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofNoFill();
	ofRect(center.x + modes[modeId]->centerOffX,center.y + modes[modeId]->centerOffY,modes[modeId]->randomX*2,modes[modeId]->randomY*2);
	ofPushStyle();
}

void TargetCanon::drawGui(int modeId){
	modes[modeId]->gui.draw();
}

void TargetCanon::shootNextTarget() {
	ofPoint center(ofGetWidth() / 2.f, ofGetHeight() / 2.f);

	Target * target = new Target();

	float angle = 90 + ofRandom(mode->minAngle, mode->maxAngle);
	float tx = center.x + mode->centerOffX + mode->radius * cos(ofDegToRad(angle));
	float ty = center.y + mode->centerOffY + mode->radius * sin(ofDegToRad(angle));

	target->setPhysics(mode->density, mode->bounce, mode->friction);
	target->setup(arenaPtr->getBox2d().getWorld(), tx, ty); //TODO use type instead of w,h

	float atx = center.x + mode->centerOffX + ofRandom(-mode->randomX,mode->randomX);
	float aty = center.y + mode->centerOffY + ofRandom(-mode->randomY,mode->randomY);

	target->addAttractionPoint(atx, aty, mode->attractionAmt); //TODO impulse instead of force?
	target->body->SetAngularVelocity(ofRandom(mode->angularVel));
	//TODO density to size factor

	arenaPtr->addTarget(target);
}

void TargetCanon::nextMode(){
	modeIdx = (modeIdx + 1) % NUM_MODES;
	mode = modes[modeIdx];
}

} /* namespace Box2dArena */
