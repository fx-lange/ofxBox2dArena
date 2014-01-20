#include "ofMain.h"

#pragma once

namespace Box2dArena {

#define HIT 50
#define FAIL 10

struct HitPoint {
	ofVec2f pos;
	long timestamp;

	HitPoint(ofVec2f pos, long timestamp) {
		this->pos = pos;
		this->timestamp = timestamp;
	}
};

class Score {
public:
	Score();
	virtual ~Score();

	void setup(string font);
	void update(float hpDuration, float drifting = 0);

	void draw(float x, float y);
	void addHit(ofVec2f pos);
	void addFail(ofVec2f pos);

	void stopCounting(bool stopCounting);

	int getTotal();
private:
	bool bCount;
	int total;
	ofTrueTypeFont font, hitFont;
	list<HitPoint> hitPoints;
};

} /* namespace Box2dArena */
