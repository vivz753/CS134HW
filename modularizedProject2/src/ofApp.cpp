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
	//gui.setup();
	//gui.add(firingRateSlider.setup("rate", 2, 0, 20));
	//gui.add(velocitySlider.setup("Velocity", ofVec3f(0, 450, 0), ofVec3f(-3000, -3000, 0), ofVec3f(3000, 3000, 0)));
	//gui.add(lifeSpanSlider.setup("lifespan", 1500, 0, 1000));

	//set images for emitter & sprites
	gunEmitter = Emitter();
	gunEmitter.gunInit();
	//set emitter properties based off of GUI sliders
	//gunEmitter.setRate(firingRateSlider);	
	//gunEmitter.setVelocity(ofVec3f(velocitySlider));
	/*gunEmitter.setLifespan(lifeSpanSlider);*/

	//create enemy emitters
	int numEmitters = 1;
	float margin = 50;
	float enemyWidth = 50;
	float x = enemyWidth / 2 + margin;
	float spacing = (ofGetWindowWidth() - enemyWidth - margin * 2) / (numEmitters - 1);

	gun.load("bow.png");
	bullet.load("arrow.png");
	gunEmitter.setChildImage(bullet);
	gunEmitter.setImage(gun);

	bullet.load("skull.png");
	
	for (int i = 0; i < numEmitters; i++) {
		Emitter *enemy = new Emitter();
	/*	enemy->setRate(firingRateSlider);
		enemy->setVelocity(ofVec3f(velocitySlider));
		enemy->setLifespan(lifeSpanSlider);*/
		enemy->enemiesInit(gunEmitter.maxDistPerFrame());
		enemy->setPosition(ofVec3f(x, 0, 0));
		enemy->setChildImage(bullet);
		x += spacing;
		enemies.push_back(enemy);
		enemy->start();
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < sizeof(keyIsDown); i++) {
		if (keyIsDown[i]) {
			gunEmitter.moving = true;
		}
	}
	gunEmitter.update();

	for (int i = 0; i < enemies.size(); i++) {
		
		//enemies[i]->setRate(firingRateSlider);
		//enemies[i]->setVelocity(ofVec3f(velocitySlider));
		//enemies[i]->setLifespan(lifeSpanSlider);
		enemies[i]->update();
	}
	
	//update properties based off of GUI sliders
	//gunEmitter.setRate(firingRateSlider);
	//gunEmitter.setVelocity(ofVec3f(-velocitySlider->x, -velocitySlider->y, 0));
	/*gunEmitter.setLifespan(lifeSpanSlider);*/

	if (gunEmitter.started) {
		checkCollisions();
		checkHealth();
	}
	
	
	
}

//--------------------------------------------------------------
void ofApp::draw() {


	//draw background image
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);

	

	
	

	//draw GUI when game begins
	if (gunEmitter.started) {
		//gui.draw();
		gunEmitter.draw();
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->draw();
		}
		text.drawString("score: " + to_string(gunEmitter.score), 50, 50);
		text.drawString("hp: " + to_string(gunEmitter.hp), 50, 90);
		text.drawString("press q to quit", ofGetWindowWidth() - 300, ofGetWindowHeight()-50);
	}

	//draw start menu text
	else if (gunEmitter.dead) {
		text.drawString("you died; press r to restart", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
	}
	
	else{
		text.drawString("press spacebar to begin", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
	}

}

void ofApp::checkHealth() {
	if (gunEmitter.started) {
		if (gunEmitter.hp <= 0) {
			gunEmitter.stop();
			background.load("jonsnow.jpg");
			bgMusic.load("winterfell.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
			gunEmitter.dead = true;
		}
		
	}
	
}

void ofApp::checkCollisions() {
	float dist = gunEmitter.maxDistPerFrame();

	vector<Sprite>::iterator j = gunEmitter.sys.sprites.begin();
	

	////check if enemies hit the gunEmitter; if they do, lose 5hp
	////BROKEN!
	
	//}

	////same attempt as above, but game doesn't load
	////BROKEN!
	//if (enemies[0]->sys.collided(gunEmitter.trans, dist)) {
	//	cout << "-5 hp" << endl;
	//}


	while (j != gunEmitter.sys.sprites.end()) {
		

		if (enemies[0]->sys.removeNear(j->trans, dist) 
			//||
			//enemies[1]->sys.removeNear(j->trans, dist) ||
			//enemies[2]->sys.removeNear(j->trans, dist)
			) 
		{
			gunEmitter.sys.remove(j);
		
			gunEmitter.score += 15;
		
		}
		else {
			j++;
		}


		
}
	vector<Sprite>::iterator i = enemies[0]->sys.sprites.begin();
	while (i != enemies[0]->sys.sprites.end()) {
		if (gunEmitter.collided(i->trans, dist)) {
			//i->lifespan = 1;
			i = enemies[0]->sys.sprites.erase(i);
			break;
		}
		else {
			i++;
			break;
		}
	}

		
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	//start game upon spacebar key
	case ' ':
		//load in game elements
		if (!gunEmitter.started) {
			gunEmitter.start();
			background.load("northofthewall.jpg");
			bgMusic.load("battle.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		//shoot bullets upon spacebar key
		else if (gunEmitter.started) {
			gunEmitter.shooting = true;
		}
		break;
	//quit game upon q key
	case 'q':
		//load start menu elements
		if (gunEmitter.started) {
			gunEmitter.stop();
			background.load("gotmenu.jpg");
			bgMusic.load("gottheme.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		break;
	case 'w':
		keyIsDown[0] = true;
		gunEmitter.movingVector.y = -300;
		break;
	case 'a':
		keyIsDown[1] = true;
		gunEmitter.movingVector.x = -300;
		break;
	case 's':
		keyIsDown[2] = true;
		gunEmitter.movingVector.y = 300;
		break;
	case 'd':
		keyIsDown[3] = true;
		gunEmitter.movingVector.x = 300;
		break;
	case 'r':
		if (gunEmitter.dead) {
			gunEmitter.start();
			background.load("northofthewall.jpg");
			bgMusic.load("battle.mp3");
			bgMusic.play();
			bgMusic.setLoop(true);
		}
		break;
}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key) {
		//stop moving
	case 'w':
		keyIsDown[0] = false;
		gunEmitter.movingVector.y = 0;
		break;

	case 'a':
		keyIsDown[1] = false;
		gunEmitter.movingVector.x = 0;
		break;
	case 's':
		keyIsDown[2] = false;
		gunEmitter.movingVector.y = 0;
		break;
	case 'd':
		keyIsDown[3] = false;
		gunEmitter.movingVector.x = 0;
		break;
		//stop shooting
	case ' ':
		if (!pressingMouse) gunEmitter.shooting = false;
		break;
	}


	

	
	
	if (gunEmitter.moving) {
		gunEmitter.moving = false;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	//emitter follows mouse movement
	//cout << "mouse: " << x << "," << y << endl;
	//cout << "gun: " << gunEmitter.trans.x << "," << gunEmitter.trans.y << endl;
	gunEmitter.translate(x, y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//emitter shoots and follows mouse movement
	gunEmitter.translate(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//emitter shoots
	if (gunEmitter.started) {
		gunEmitter.shooting = true;
	}
	pressingMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	//stop shooting
	gunEmitter.shooting = false;
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
