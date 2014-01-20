#include "ofMain.h"

#pragma once

namespace Box2dArena {

#define HIT 5
#define FAIL 15

class Score {
public:
	Score();
	virtual ~Score();

	void setup(string font);

	void draw();
	void addHit(ofVec2f pos);
	void addFail(ofVec2f pos);
private:
	int total;
	ofTrueTypeFont font;
};

} /* namespace Box2dArena */
