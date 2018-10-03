//  CS 134 - In-Class exercise - Getting started with Particle Physics
//
//  This is fairly comprehensive example of how to use an emitter setup in
//  "one shot" mode with various types of external forecs such as 
//  gravity, turbulence, cyclic, radial.   
//
//  All of the emitter parameters are connected to sliders in order to vary
//  mass, damping, number of particles created.
//
//  All of the force parameters are also connected to sliders. Each force
//  has it's own parameter(s) that are specific to that type of force.
//
//  You can easily extend the system with any types of new/weird forces you want
//  to experiment with.  (look at CyclicForce as an example)
//
//  I have also demonstarted a way to render particles using a textures, shaders
//  and the VBO  (Vertex Buffer).  You will need the textures dot.png file to 
//  be installed in your data/images directory.
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
	ofSetBackgroundColor(ofColor::black);

	// texture loading
	//
	ofDisableArbTex();     // disable rectangular textures

	// load textures
	//
	if (!ofLoadImage(particleTex, "images/dot.png")) {
		cout << "Particle Texture File: images/dot.png not found" << endl;
		ofExit();
	}

	// load the shader
	//
#ifdef TARGET_OPENGLES
	shader.load("shaders_gles/shader");
#else
	shader.load("shaders/shader");
#endif


	// some simple sliders to play with parameters
	//
	gui.setup();
//	gui.add(velocity.setup("Initial Velocity", ofVec3f(0, 20, 0), ofVec3f(0, 0, 0), ofVec3f(100, 100, 100)));	
//	gui.add(lifespan.setup("Lifespan", 2.0, .1, 10.0));(
	gui.add(numParticles.setup("Number of Particles", 10000, 0, 25000));
	gui.add(lifespanRange.setup("Lifespan Range", ofVec2f(1, 6), ofVec2f(.1, .2), ofVec2f(3, 10)));
	gui.add(mass.setup("Mass", 1, .1, 10));
//	gui.add(rate.setup("Rate", 1.0, .5, 60.0));
	gui.add(damping.setup("Damping", .99, .8, 1.0));
    gui.add(gravity.setup("Gravity", 0, -20, 20));
	gui.add(radius.setup("Radius", 5, 1, 10));
	gui.add(turbMin.setup("Turbulence Min", ofVec3f(0, 0, 0), ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)));
	gui.add(turbMax.setup("Turbulence Max", ofVec3f(0, 0, 0), ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)));
	gui.add(radialForceVal.setup("Radial Force", 1000, 100, 5000));
	gui.add(radialHight.setup("Radial Height", .2, .1, 1.0));
	gui.add(cyclicForceVal.setup("Cyclic Force", 0, 10, 500));
	bHide = false;

	// Create Forces
	//
	turbForce = new TurbulenceForce(ofVec3f(turbMin->x, turbMin->y, turbMin->z), ofVec3f(turbMax->x, turbMax->y, turbMax->z));
	gravityForce = new GravityForce(ofVec3f(0, -gravity, 0));
	radialForce = new ImpulseRadialForce(radialForceVal);
	cyclicForce = new CyclicForce(cyclicForceVal);

	// set up the emitter
	// 
	emitter.sys->addForce(turbForce);
	emitter.sys->addForce(gravityForce);
	emitter.sys->addForce(radialForce);
	emitter.sys->addForce(cyclicForce);

	emitter.setVelocity(ofVec3f(0, 0, 0));
	emitter.setOneShot(true);
	emitter.setEmitterType(RadialEmitter);
	emitter.setGroupSize(numParticles);
	emitter.setRandomLife(true);
	emitter.setLifespanRange(ofVec2f(lifespanRange->x, lifespanRange->y));
}

// load vertex buffer in preparation for rendering
//
void ofApp::loadVbo() {
	if (emitter.sys->particles.size() < 1) return;

	vector<ofVec3f> sizes; 
	vector<ofVec3f> points;
	for (int i = 0; i < emitter.sys->particles.size(); i++) {
		points.push_back(emitter.sys->particles[i].position);
		sizes.push_back(ofVec3f(radius));
	}
	// upload the data to the vbo
	//
	int total = (int)points.size();
	vbo.clear();
	vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
	vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
}

//--------------------------------------------------------------
//
void ofApp::update() {
	ofSeedRandom();

	// live update of emmitter parameters (with sliders)
	//
	emitter.setParticleRadius(radius);
	emitter.setLifespanRange(ofVec2f(lifespanRange->x, lifespanRange->y));
	emitter.setMass(mass);
	emitter.setDamping(damping);
	emitter.setGroupSize(numParticles);

	// live update of forces  (with sliders)
	//
	gravityForce->set(ofVec3f(0, -gravity, 0));
	turbForce->set(ofVec3f(turbMin->x, turbMin->y, turbMin->z), ofVec3f(turbMax->x, turbMax->y, turbMax->z));
	radialForce->set(radialForceVal);
	radialForce->setHeight(radialHight);
	cyclicForce->set(cyclicForceVal);

	// don't forget to update emitter
	//
	emitter.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	loadVbo();

	// draw the GUI
	if (!bHide) gui.draw();

	// draw a grid
	//
	cam.begin();
	ofPushMatrix();
	ofRotateDeg(90, 0, 0, 1);
	ofSetLineWidth(1);
	ofSetColor(ofColor::dimGrey);
	ofDrawGridPlane();
	ofPopMatrix();
	cam.end();

	glDepthMask(GL_FALSE);

	ofSetColor(255, 100, 90);

	// this makes everything look glowy :)
	//
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnablePointSprites();


	// begin drawing in the camera
	//
	shader.begin();
	cam.begin();

	// draw particle emitter here..
	//
//	emitter.draw();
	particleTex.bind();
	vbo.draw(GL_POINTS, 0, (int)emitter.sys->particles.size());
	particleTex.unbind();

	//  end drawing in the camera
	// 
	cam.end();
	shader.end();

	ofDisablePointSprites();
	ofDisableBlendMode();
	ofEnableAlphaBlending();

	// set back the depth mask
	//
	glDepthMask(GL_TRUE);

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
