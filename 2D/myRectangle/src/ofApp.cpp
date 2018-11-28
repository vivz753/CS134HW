#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	/*ofSetColor(ofColor::red);*/
	rect.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	cout << "dragging" << x << ")" << endl;
	if (rect.clickedInside) rect.translate(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	rect.clicked(x, y);
	cout << rect.pos << endl;
	//cout << "(" << x << "," << y << ")" << endl;
	//if (rect.inside(x, y)) {
	//	rect.switchColors();
	//	cout << "hit";
	//}
	//	
	//else {
	//	cout << "miss";
	//}
		
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	rect.released();
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
