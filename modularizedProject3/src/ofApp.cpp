#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	setScreen(home);
	screen->init();
}

//--------------------------------------------------------------
void ofApp::update(){
	screen->update();

	if (screen -> transition) {
		switch (screen->transitionScreen) {
		case INGAME:
			setScreen(inGame);
			setLevel(home->transitionLevel);
			break;
		case HOME:
			setScreen(home);
			break;
		}
		
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	screen->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	screen->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	screen->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	screen->mouseMoved(x, y);
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
