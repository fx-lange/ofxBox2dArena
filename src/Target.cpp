#include "Target.h"

namespace Box2dArena {

vector<ofImage> Target::images = vector<ofImage>();
bool Target::imagesLoaded = false;

void Target::loadImages(){
	ofDirectory dir;
	dir.open("targets");
	dir.listDir();
	for(int i=0;i<(int)dir.size();++i){
		ofImage img;
		img.loadImage(dir.getFile(i));
		img.resize(img.width/4,img.height/4);
		images.push_back(img);
	}
}

void Target::setup(b2World * b2dworld, float x, float y){
	if(!imagesLoaded){
		imagesLoaded = true;
		loadImages();
	}
	int dice = ofRandom(0,images.size());
	img = &images[dice];
	ofxBox2dRect::setup(b2dworld,x,y,img->width,img->height); //TODO percentage of size?
}

Target::Target() :
		bHit(false), bEnteredArena(false), img(NULL) {
	color.set(255, 255, 255);
}

Target::~Target() {
}

void Target::draw() {
	ofSetColor(color);
	if(bHit)
		ofxBox2dRect::draw();
	ofVec2f pos = ofxBox2dBaseShape::getPosition();
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(ofxBox2dBaseShape::getPosition());
	ofRotate(getRotation());
	ofSetRectMode(OF_RECTMODE_CENTER);
	img->draw(0,0);
	ofPopStyle();
	ofPopMatrix();
}

} /* namespace Box2dArena */
