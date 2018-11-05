#include "InGameScreen.h"
#include <cmath>
#include <iostream>

InGameScreen::InGameScreen() {
	
	//initial settings
	screenType = INGAME;
	levelType = Level1;


	//playerScore is a global variable throughout the levels
	playerScore = 0;
};

void InGameScreen::setLevel(LevelType level) {
	//every time we change levels, stop the emitters, and then init()
	gunEmitter.stop();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

	levelType = level;
	init();
};

//only use this to transition from level 1 to level 2 to level 3
void InGameScreen::setLevel(int level) {
	
	switch (level) {
	case 1:
		setLevel(Level1);
		break;
	case 2:
		setLevel(Level2);
		break;
	case 3:
		setLevel(Level3);
		break;
	}
}

//this is run everytime a level is switched, or when user starts game, or when user selects a specific level
void InGameScreen::init()
{

	//player HP gets reset at each level
	gunEmitter.hp = 500;

	//only create the gunEmitter once
	gunEmitter = Emitter(GUN);
	
	//create one particle system for collision effets
	pe = new ParticleEmitter();

	switch (levelType) {
	case Level1:
		beatLevelOne = false;
		emitterA = Emitter(EMITTERA);
		emitterB = Emitter(EMITTERB);
		emitterB2 = Emitter(EMITTERB);


		emitters.push_back(emitterA);

		emitterB.sys->applySinMovement(-1);
		emitters.push_back(emitterB);

		emitterB2.sys->applySinMovement(1);
		emitters.push_back(emitterB2);

		cout << "emitter size: " << emitters.size() << endl;
		cout << "switched to level 1" << endl;
		break;
	case Level2:

		//emitterA.init();
		emitterA = Emitter(EMITTERA);
		emitterA.sys->applySinMovement(1);
		emitters.push_back(emitterA);

		emitterB = Emitter(EMITTERB);
		emitterB2 = Emitter(EMITTERB);

		emitterB.sys->applySinMovement(1);
		emitters.push_back(emitterB);
		

		emitterB2.setPosition(ofVec3f(0, -100, 0));
		emitterB2.sys->applySinMovement(-1);
		emitters.push_back(emitterB2);

		cout << "emitter size: " << emitters.size() << endl;
		
		cout << "switched to level 2" << endl;
		break;
	case Level3:



		catPumpkinBoss = Emitter(EMITTERC);
		//emitters.push_back(emitterC);
		
		cout << "emitter size: " << emitters.size() << endl;
		cout << "switched to level 3" << endl;
		break;
	}
	
	////initialize start menu elements
	//text.load("arial.ttf", 32);
	//background.load("northofthewall.jpg");

	////load starting bg music
	//bgMusic.load("battle.mp3");
	//bgMusic.play();
	//bgMusic.setLoop(true);
};

void InGameScreen::terminate() {

	//stop music, reset transition variable, set the level back to 1, reset score
	bgMusic.stop();
	transition = false;
	levelType = Level1;
	playerScore = 0;

	//stop emitters from firing
	
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

}

void InGameScreen::draw()
{
	//draw background image
	/*background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);*/
	/*text.drawString(to_string(gunEmitter.hp), 50, 50);
	text.drawString(to_string(playerScore), 50, 150);*/
	ofClear(0);
	ofDrawBitmapString("HP: " + to_string(gunEmitter.hp), 20, 20);
	ofDrawBitmapString(to_string(playerScore), 20, 40);

	
	

	switch (levelType) {
	case Level1:
	
		ofDrawBitmapString("LEVEL 1: S to start, Q to quit, SPACE to fire", 20, ofGetWindowHeight() - 20);
		
		break;
	case Level2:
		
		ofDrawBitmapString("LEVEL 2", 20, ofGetWindowHeight() - 20);

		break;
	case Level3:
		catPumpkinBoss.draw();
		ofDrawBitmapString("LEVEL 3", 20, ofGetWindowHeight() - 20);

		break;
	}

	//draw gun
	gunEmitter.draw();

	
	//draw all enemy emitters
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].draw();
	}

	//draw particlesystem for collisions
	pe->draw();

};

void InGameScreen::update() {
	
	//update gun
	gunEmitter.update();

	//update enemy emitters
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].update();
	}

	//check if bullets hit enemy sprites
	checkCollisions();

	switch (levelType) {
	
	case Level1:
		if (playerScore >= 500 && !beatLevelOne) {
			beatLevelOne = true;
			setLevel(2);
		}
		break;
	case Level2:
		if (playerScore >= 1500 && beatLevelOne) {
			setLevel(3);
		}
		break;
	case Level3:
		catPumpkinBoss.update();
		if (catPumpkinBoss.hp <= 0) {
			transition = true;
			transitionScreen = HOME;
		}
		break;
	}

	//if hp hits 0 or below, transition the screen to home
	if (gunEmitter.hp <= 0) {
		transition = true;
		transitionScreen = HOME;

	}

	pe->update();

};

void InGameScreen::checkCollisions() {

	switch (levelType) {
	case Level3:
		catPumpkinBoss.checkCollision(gunEmitter.sys);
		gunEmitter.checkCollision(catPumpkinBoss.sys);
		gunEmitter.sys->checkCollisions(catPumpkinBoss.sys, pe);
		break;
	}


	for (size_t i = 0; i < emitters.size(); i++) {
		//checks if bullets hit emitter enemy sprites
		/*pe->update();*/

		//update playerScore everytime there is a collision (edit point amount in SpriteSystem checkCollisions method)
		playerScore += gunEmitter.sys->checkCollisions(emitters[i].sys, pe);
		

		//checks if emitter enemy sprites hit the gun emitter; removes health if there is a collision
		gunEmitter.checkCollision(emitters[i].sys);

		//check if emitters are collindg w/ gun
		gunEmitter.checkCollision(emitters[i]);

		//check if any emitters are hit by bullets
		emitters[i].checkCollision(gunEmitter.sys);
		
		
	}

	

};

void InGameScreen::keyPressed(int key) {
	switch (key) {
	case ' ':
		//start gun emitter
		gunEmitter.start();
		break;
	case 's':
		//start emitters
		for (size_t i = 0; i < emitters.size(); i++) {
			emitters[i].start();
		}

		if (levelType == Level3) {
			catPumpkinBoss.start();
		}
		/*catPumpkinBoss.start();
		switch (levelType) {
		case Level3:
			catPumpkinBoss.start();
			break;
		}*/
		break;
	case 'q':
		transition = true;
		transitionScreen = HOME;
		break;

	}
};

void InGameScreen::keyReleased(int key) {
	switch (key) {
	case ' ':
		//only stop the gunEmitter from firing when space is released
		gunEmitter.stop();
		break;
	}
};

void InGameScreen::mouseMoved(int x, int y) {
		gunEmitter.translate(x, y);
};

void InGameScreen::mousePressed(int x, int y, int button) {
	gunEmitter.start();
};

void InGameScreen::mouseDragged(int x, int y, int button) {
	gunEmitter.start();
	gunEmitter.translate(x, y);
};

void InGameScreen::mouseReleased(int x, int y, int button) {
	gunEmitter.stop();
};