#include "Arena.h"

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
	gui.setup("arena", "arena.xml", 300, 50);
	gui.add(gravity.setup("gravity", 1, 0, 5));
	gui.loadFromFile("arena.xml");
}

void Arena::update() {
	box2d.setGravity(0, gravity); //TODO every frame?!
	box2d.update();
}

void Arena::draw() {
	for (int i = 0; i < (int) targets.size(); i++) {
		targets[i]->draw();
	}
}

ofxBox2d & Arena::getBox2d() {
	return box2d;
}

} /* namespace Box2dArena */
