#include "ofApp.h"
#include "Emitter.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("gotmenu.jpg");

	//load starting bg music
	bgMusic.load("gottheme.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);

	//construct GUI
	gui.setup();
	gui.add(firingRateSlider.setup("rate", 10, 0, 20));
	gui.add(velocitySlider.setup("Velocity", ofVec3f(0, -1000, 0), ofVec3f(-3000, -3000, 0), ofVec3f(3000, 3000, 0)));
	gui.add(lifeSpanSlider.setup("lifespan", 500, 0, 1000));

	//set images for emitter & sprites
	gun.load("jar.png");
	bullet.load("cookie.png");
	emitter.setChildImage(bullet);
	emitter.setImage(gun);

	//set emitter properties based off of GUI sliders
	emitter.setRate(firingRateSlider);	v = ofVec3f(velocitySlider);
	
	emitter.setVelocity(v);
	emitter.setLifespan(lifeSpanSlider);
}

//--------------------------------------------------------------
void ofApp::update(){

	emitter.update();
	v = ofVec3f(velocitySlider);
	//update properties based off of GUI sliders
	emitter.setRate(firingRateSlider);
	emitter.setVelocity(v);
	emitter.setLifespan(lifeSpanSlider);
	
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	//draw background image
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);

	emitter.draw();

	//draw GUI when game begins
	if (emitter.started) {
		gui.draw();
	}

	//draw start menu text
	else {
		text.drawString("press spacebar to begin", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	//start game upon spacebar key
	case ' ':
		//load in game elements
		if (!emitter.started) {
			emitter.start();
			background.load("jonsnow.jpg");
			bgMusic.load("winterfell.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		//shoot bullets upon spacebar key
		else if (emitter.started) {
			emitter.shooting = true;
		}
		break;
	//quit game upon q key
	case 'q':
		//load start menu elements
		if (emitter.started) {
			emitter.stop();
			background.load("gotmenu.jpg");
			bgMusic.load("gottheme.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		break;


	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//stop shooting
	if(!pressingMouse) emitter.shooting = false;

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//emitter follows mouse movement
	emitter.translate(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//emitter shoots and follows mouse movement
	emitter.translate(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//emitter shoots
	if (emitter.started) {
		emitter.shooting = true;
	}
	pressingMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//stop shooting
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
