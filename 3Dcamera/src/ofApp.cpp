#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::black);	/*sets background color to black so white box is easier to see*/
	bHide = false;
	gui.setup();
	gui.add(camDistance.setup("camera distance", 20, 10, 50));
	cam.setDistance(camDistance);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.setDistance(camDistance);
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(!bHide) gui.draw();
	cam.begin();
	ofNoFill();
	ofDrawBox(10,20,30);   /* this creates a cube*/
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'C':
	case 'c':
		if (cam.getMouseInputEnabled()) cam.disableMouseInput();
		else cam.enableMouseInput();
		break;
	case 'F':
	case'f':
		ofToggleFullscreen();
		break;
	case 'h':
		bHide = !bHide;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
