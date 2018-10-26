//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  Kevin M. Smith - CS 134 - SJSU CS

#include "ofApp.h"






//--------------------------------------------------------------
//  Setup Application data
//
void ofApp::setup(){
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	ofSetFrameRate(60);


	// some simple sliders to play with parameters
	//
	gui.setup();
	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 20, 0), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));	
	gui.add(lifespan.setup("Lifespan", 2.0, .1, 10.0));
	gui.add(rate.setup("Rate", 1.0, .5, 60.0));
	gui.add(damping.setup("Damping", .99, .1, 1.0));
    gui.add(gravity.setup("Gravity", 10, 1, 20));
	gui.add(radius.setup("Radius", .1, .01, .3));
	bHide = false;


	//10/8/2018 - In class exercise
	turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)); 
	gravityForce = new GravityForce(ofVec3f(0, -10, 0));
	ringRadialForce = new ImpulseRadialForce(1000, -.1, .1);
	sphereRadialForce = new ImpulseRadialForce(1000, -1, 1);

	emitter.sys->addForce(turbForce);
	emitter.sys->addForce(gravityForce);
	//emitter.sys->setHeight(-1, 1);
	emitter.sys->addForce(ringRadialForce);
	emitter.setVelocity(ofVec3f(0, 0, 0));
	emitter.setOneShot(true);
	//emitter.setEmitterType(RadialEmitter);
	emitter.setGroupSize(100);
	

	
	//emitter2.sys->setHeight(-.1, .1);
	emitter2.sys->addForce(sphereRadialForce);
	emitter2.setOneShot(true);
	emitter2.setGroupSize(100);
	emitter2.sys->addForce(turbForce);

	// start up the emitter
	// 
	/*emitter.sys->addForce(new TurbulenceForce(ofVec3f(-2, -1, -3), ofVec3f(1, 2, 5)));
	emitter.sys->addForce(new GravityForce(ofVec3f(0, -gravity, 0)));*/
}

//--------------------------------------------------------------
//
void ofApp::update() {
	ofSeedRandom();

	emitter.setLifespan(lifespan);
	emitter2.setLifespan(lifespan);
	emitter2.setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
	emitter2.setRate(rate);
	emitter2.setParticleRadius(radius);
	emitter.setParticleRadius(radius);

	emitter.update();
	emitter2.update();
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
	ofRotateDeg(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();

	// draw particle emitter here..
	//
	emitter.draw();
	emitter2.draw();


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
	case 'b':
		break;
	case 'f':
		ofToggleFullscreen();
		break;
	case 'h':
		bHide = !bHide;
	case ' ':
		emitter.sys->reset();
		emitter.start();
		emitter2.sys->reset();
		emitter2.start();
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
