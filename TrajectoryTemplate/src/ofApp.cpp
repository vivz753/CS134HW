//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  Kevin M. Smith - CS 134 - SJSU CS

//[x] set particle.velocity.x = velocity->x; and for y and z to fix error
//1) modify App::launchParticle() to create a new particle and store in an array. Use values from GUI parameters to create your particle
//2) Modify App::draw() to draw particles in array (call each particle's draw method in a loop
//3) you should just have one particle in middle, but you shuld at least be able to modify it's radius w/ the slider before launching it with spacebar
//4) Complete integrator function (3-4 lines of code) based on the algorithm we learned today
//	p' = p + vt
//	v' = v + at

//completed by Vivian Leung on September 26, 2018
//added Vector<Particle> particles to the header file, finished the integrate() method and added it to the ofApp:update() method, and added Particle objects to particles in launchParticle() 


#include "ofApp.h"


Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = .5;
	damping = .99;
	mass = 1;
}

void Particle::draw() {

	ofSetColor(ofColor::blue);
	ofDrawSphere(position, radius);


}

// write your own integrator here.. (hint: it's only 3 lines of code)
//
void Particle::integrate() {
	float dt = 1 / ofGetFrameRate();
	position.set(position.x + velocity.x*dt, position.y + velocity.y*dt, position.z + velocity.z*dt);
	velocity.set(velocity.x + acceleration.x*dt, velocity.y + acceleration.y*dt, velocity.z + acceleration.z*dt);
	velocity.set(velocity.x*damping, velocity.y*damping, velocity.z*damping);
	// (1) update position from velocity and time interval
	// (2) update acceleration from velocity and time interval
	// (3) multiply final result by damping factor to sim drag
	//
} 

void ofApp::launchParticle() {

	// Create initialize a new particle with values from sliders
	//
	Particle particle;
	particle.velocity.x = velocity->x;
	particle.velocity.y = velocity->y;
	particle.velocity.z = velocity->z;
	particle.acceleration.set(0, -gravity, 0);
	particle.damping = damping;
	particle.radius = radius;

	cout << "vel: " << particle.velocity << endl;
	cout << "accel: " << particle.acceleration << endl;
	cout << "damp: " << damping << endl;
	cout << "rad: " << radius << endl;

	// save your particle here (suggestion: put it into a vector array)
	//
	
	particles.push_back(particle);
}

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setDistance(10);
	cam.setNearClip(.1);
	cam.setFov(65.5);   // approx equivalent to 28mm in 35mm format
	ofSetVerticalSync(true);
	framerate = ofGetFrameRate();

	// some simple sliders to play with parameters
	//
	gui.setup();
	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 20, 0), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));	
	gui.add(damping.setup("Damping", .99, .1, 1.0));
    gui.add(gravity.setup("Gravity", 10, 1, 20));
	gui.add(radius.setup("Radius", .5, .1, 1.0));
	bHide = false;

	
	display.radius = radius;
	
}

//--------------------------------------------------------------
void ofApp::update() {
	//
	// need to call integrate() method in your particles here
	//
	for (int i = 0; i < particles.size(); i++) {
		particles[i].integrate();
	}

	display.radius = radius;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);

	// draw the GUI
	if (!bHide) gui.draw();


	cam.begin();

	// draw a grid
	//
	ofPushMatrix();
	ofRotate(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();

	// draw particle(s) here..
	//give the user an idea of how big the particle will be
	display.draw();
	//
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}


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
	case 'f':
		ofToggleFullscreen();
		break;
	case ' ':
		launchParticle();
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
