#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	setScreen(home);
	screen->init();
}

//--------------------------------------------------------------
void ofApp::update(){
	screen->update();
	if (screen->transition) {
		switch (screen->transitionScreen) {
		case HOME:
			setScreen(home);
			break;
		case INGAME:
			if (screen->screenType = HOME) {
				cout << home->transitionLevel << endl;
				inGame->setLevel(home->transitionLevel);
			}
			//else if screenType=LOSE, replay the level that the player lost at
			cout << "home transition Level: " + home->transitionLevel << endl;
			setScreen(inGame);
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
	//switch (screen->screenType) {
	//case HOME:
	//	switch (key) {
	//	case 's':	
	//		setScreen(inGame);
	//		break;
	//	/*case 'l':
	//		setScreen(selectLevel);
	//		break;*/
	//	}
	//	break;
	//case INGAME:
	//	switch (key) {
	//	case 'q':
	//		setScreen(home);
	//		cout << "pressing q" << endl;
	//		break;
	//	}
	//	break;
	//}
	screen->keyPressed(key);
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
