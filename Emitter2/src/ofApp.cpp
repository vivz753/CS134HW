#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
	emitter.update();
	//emitter.sys.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
		emitter.draw();
		//emitter.sys.draw();
	//sprite.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case'f':
		if (!emitter.started) {
			emitter.start();
		}
		break;
	case 'd':
		if (emitter.started) {
			emitter.shooting = true;
		}
		break;
	case 'q':
		if (emitter.started==1) {
			emitter.stop();
		}
		break;

	}
	//space to shoot the sprites
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//stop shooting
	emitter.shooting = false;
	cout << "released key" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	emitter.translate(x, y);

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
