/*
 * Game.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: felix
 */

#include "Game.h"

namespace Box2dArena {

Game::Game() :
		canonPtr(NULL), targetsToShoot(0), tLastUpdate(-1) {
}

Game::~Game() {
}

void Game::setup(TargetCanon * canon) {
	canonPtr = canon;

	setupGui();
}

void Game::setupGui() {
	gui.setup("game", "arena.xml", 650, 60);
	gui.add(targetsPerSec.setup("targets per sec", 1, 0, 15));
	gui.loadFromFile("arena.xml");
}

void Game::update() {
	long tNow = ofGetElapsedTimeMillis();

	if(tLastUpdate < 0){
		tLastUpdate = tNow;
	}

	targetsToShoot += (tNow - tLastUpdate)/1000.f * targetsPerSec;

	int shots = floor(targetsToShoot);
	targetsToShoot -= (float)shots;
	for(int i=0;i<shots;++i){
		canonPtr->shootNextTarget();
	}

	tLastUpdate = tNow;
}

} /* namespace Box2dArena */
