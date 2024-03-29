#pragma once

#include "ofMain.h"

#include "Arena.h"
#include "TargetCanon.h"
#include "Player.h"
#include "Game.h"

class arenaApp: public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	Box2dArena::Arena arena;
	Box2dArena::TargetCanon canon;
	Box2dArena::Player player;
	Box2dArena::Game game;
};
