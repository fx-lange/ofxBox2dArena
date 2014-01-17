#include "TargetCanon.h"

#pragma once

namespace Box2dArena {

class Game {
public:
	Game();
	virtual ~Game();

	void setup(TargetCanon * canon);
	void update();

private:
	TargetCanon * canonPtr;
};

} /* namespace Box2dArena */
