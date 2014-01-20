#include "Target.h"

namespace Box2dArena {

vector<ofImage> Target::images = vector<ofImage>();
vector<ofImage> Target::brokenImages = vector<ofImage>();
bool Target::imagesLoaded = false;

void Target::loadImages() {
	ofDirectory targetsDir;
	targetsDir.open("targets");
	targetsDir.listDir();
	ofImage img;
	for (int i = 0; i < (int) targetsDir.size(); ++i) {
		ofDirectory dir;
		dir.open(targetsDir.getPath(i));
		dir.listDir();
		dir.sort();
		img.loadImage(dir.getFile(0));
		img.resize(img.width / 2, img.height / 2);
		images.push_back(img);
		img.loadImage(dir.getFile(1));
		img.resize(img.width / 2, img.height / 2);
		brokenImages.push_back(img);
	}
}

void Target::setup(b2World * b2dworld, float x, float y) {
	if (!imagesLoaded) {
		imagesLoaded = true;
		loadImages();
	}
	int dice = ofRandom(0, images.size());
	img = &images[dice];
	brokenImg = &brokenImages[dice];
	ofxBox2dRect::setup(b2dworld, x, y, img->width, img->height); //TODO percentage of size?
}

Target::Target() :
		bHit(false), bEnteredArena(false), bMissed(false), img(NULL), brokenImg(NULL) {
	color.set(255, 255, 255);
}

Target::~Target() {
}

void Target::draw(bool debug) {
	ofPushMatrix();
	ofPushStyle();
	if(debug){
		ofSetColor(color);
	}else{
		ofSetColor(255,255,255);
	}
	ofTranslate(ofxBox2dBaseShape::getPosition());
	ofRotate(getRotation());
	ofSetRectMode(OF_RECTMODE_CENTER);
	if (bHit) {
		brokenImg->draw(0, 0);
	} else {
		img->draw(0, 0);
	}
	ofPopStyle();
	ofPopMatrix();
}

} /* namespace Box2dArena */
