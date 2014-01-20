#include "Score.h"

namespace Box2dArena {

Score::Score() :
		total(0) {
}

Score::~Score() {
}

void Score::setup(string fontName){
	font.loadFont(fontName,30,true,true,false);
}

void Score::draw(){
	font.drawString(ofToString(total),0,0);
}

void Score::addHit(ofVec2f pos){
	total += HIT;
}

void Score::addFail(ofVec2f pos){
	total -= HIT;
}

} /* namespace Box2dArena */
