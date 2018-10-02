//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  Kevin M. Smith - CS 134 - SJSU CS

#include "ofApp.h"






//--------------------------------------------------------------
//  Setup Application data
//
void ofApp::setup(){
	//*Start the Particle Emitter
	pe.start();
	
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	ofSetFrameRate(60);


	// some simple sliders to play with parameters
	//
	gui.setup();
	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 0, -100), ofVec3f(-100, -100, -100), ofVec3f(100, 100, 100)));	
	gui.add(lifespan.setup("Lifespan", 2.0, .1, 10.0));
	gui.add(rate.setup("Rate", 1.0, .5, 60.0));
	gui.add(damping.setup("Damping", .99, .1, 1.0));
    gui.add(gravity.setup("Gravity", 10, 1, 20));
	gui.add(radius.setup("Radius", .1, .01, .3));
	bHide = false;

	//*Create a new GravityForce and adjust it based on the slider 'gravity' value
	g = new GravityForce(ofVec3f(0, -gravity, 0));
	//*Add the force to the Particle Emitter's Particle System
	pe.sys->addForce(g);

	//
	// setup any objects you've created here...
	
}

//--------------------------------------------------------------
//
void ofApp::update() {
	//
	// update objects you've created here
	
	//*Set all the attributes of Particle Emitter based off of the slider values
	pe.setLifespan(lifespan);
	pe.setParticleRadius(radius);
	pe.setRate(rate);
	pe.setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));

	//*Set the GravityForce based on the slider method
	g->setGravity(ofVec3f(0,-gravity,0));
	pe.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);

	// draw the GUI
	if (!bHide) gui.draw();

	// begin drawing in the camera
	//
	cam.begin();

	// draw a grid
	//
	ofPushMatrix();
	ofRotate(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();

	//
	// draw any other objects here...
	//
	pe.draw();



	//  end drawing in the camera
	// 
	cam.end();

	// draw screen data
	//
	string str;
	str += "Frame Rate: " + std::to_string(ofGetFrameRate());
	ofSetColor(ofColor::white);
	ofDrawBitmapString(str, ofGetWindowWidth() -170, 15);
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
	case 'f':
		ofToggleFullscreen();
		break;
	case 'h':
		bHide = !bHide;
	case ' ':
		//pe.start();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//pe.stop();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//int xv = x - ofGetWindowWidth() / 2;
	//int yv = (y - ofGetWindowHeight() / 2) * -1;
	//pe.setVelocity(ofVec3f(xv, yv, velocity->z));
	//pe.setPosition(ofVec3f(xv/100, yv/100, 0));
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
