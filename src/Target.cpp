#include "Target.h"

namespace Box2dArena {

Target::Target() :
		bHit(false), bEnteredArena(false) {
	color.set(255,255,255);
}

Target::~Target() {
}

void Target::draw(){
	ofSetColor(color);
	ofxBox2dRect::draw();
}

} /* namespace Box2dArena */
