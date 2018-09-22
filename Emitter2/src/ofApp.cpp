#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	text.load("arial.ttf", 32);
	background.load("gotmenu.jpg");
	bgMusic.load("gottheme.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
	gui.setup();
	gui.add(firingRateSlider.setup("rate", 10, 0, 20));
	gui.add(velocitySlider.setup("velocity", 1000, 0, 2000));
	gui.add(lifeSpanSlider.setup("lifespan", 500, 0, 1000));
	emitter.setRate(firingRateSlider);
	emitter.setVelocity(velocitySlider);
	emitter.setLifespan(lifeSpanSlider);
}

//--------------------------------------------------------------
void ofApp::update(){
	emitter.update();
	emitter.setRate(firingRateSlider);
	emitter.setVelocity(velocitySlider);
	emitter.setLifespan(lifeSpanSlider);
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0,0);
		emitter.draw();
		if (emitter.started) {
			gui.draw();
		}
		else {
			text.drawString("press spacebar to begin", ofGetWindowWidth()*3/10, ofGetWindowHeight()*13/20);
		}
		
		//emitter.sys.draw();
	//sprite.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	//case'f':
	//	if (!emitter.started) {
	//		emitter.start();
	//		background.load("jonsnow.jpg");
	//		bgMusic.load("winterfell.mp3");
	//		bgMusic.play();
	//		bgMusic.setLoop(true);
	//	}
	//	break;
	case ' ':
		if (!emitter.started) {
			emitter.start();
			background.load("jonsnow.jpg");
			bgMusic.load("winterfell.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		else if (emitter.started) {
			emitter.shooting = true;
		}
		break;
	case 'q':
		if (emitter.started) {
			emitter.stop();
			background.load("gotmenu.jpg");
			bgMusic.load("got8bit.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		break;

	}
	//space to shoot the sprites
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//stop shooting
	if(!pressingMouse) emitter.shooting = false;
	cout << "released key" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	emitter.translate(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	emitter.translate(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (emitter.started) {
		emitter.shooting = true;
	}
	pressingMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	emitter.shooting = false;
	pressingMouse = false;
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
