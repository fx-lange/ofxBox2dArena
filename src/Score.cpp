#include "Score.h"

namespace Box2dArena {

Score::Score() :
		total(0) {
}

Score::~Score() {
}

void Score::draw(){
	cout << total << endl;
}

void Score::addHit(ofVec2f pos){
	total += HIT;
}

void Score::addFail(ofVec2f pos){
	total -= HIT;
}

} /* namespace Box2dArena */
