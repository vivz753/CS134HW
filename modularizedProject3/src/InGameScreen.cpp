#include "InGameScreen.h"
#include <cmath>
#include <iostream>

InGameScreen::InGameScreen() {
	
	//initial settings
	screenType = INGAME;
	levelType = Level1;
	beatLevelOne = false;
	beatLevelTwo = false;
	winSound.load("levelwin.wav");
	loseSound.load("levellose.wav");


	//playerScore is a global variable throughout the levels
	playerScore = 0;
};

void InGameScreen::setLevel(LevelType level) {
	//confirmedSwitch = false;
	//every time we change levels, stop the emitters, and then init()
	//gunEmitter.stop();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

	catPumpkinBoss.emitting = false;

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
		confirmedSwitch = false;
		addedEnemies = false;
		allDead = false;

		//player HP gets reset at each level
		gunEmitter.hp = 500;

		//only create the gunEmitter once
		gunEmitter = Emitter(GUN);

		//create one particle system for collision effets
		pe = new ParticleEmitter();

		switch (levelType) {
		case Level1:
			initTime = ofGetElapsedTimeMillis();
				beatLevelOne = false;

				emitterA = Emitter(EMITTERA);
				emitters.push_back(emitterA);

				emitterA2 = Emitter(EMITTERA2);	
				emitters.push_back(emitterA2);

				cout << "emitter size: " << emitters.size() << endl;
				cout << "switched to level 1" << endl;
			break;
		case Level2:
			initTime = ofGetElapsedTimeMillis();
			beatLevelTwo = false;

			emitterB = Emitter(EMITTERB);
			emitters.push_back(emitterB);

			emitterB2 = Emitter(EMITTERB);
			emitters.push_back(emitterB2);

			emitterB3 = Emitter(EMITTERB);
			emitters.push_back(emitterB3);

			emitterB4 = Emitter(EMITTERB);
			emitters.push_back(emitterB4);
			////emitterB2.sys->applySinMovement(-1);

			cout << "emitter size: " << emitters.size() << endl;
			cout << "switched to level 2" << endl;
			break;
		case Level3:
			initTime = ofGetElapsedTimeMillis();

			emitterB = Emitter(EMITTERB);
			emitters.push_back(emitterB);

			emitterA = Emitter(EMITTERA);
			emitters.push_back(emitterA);

			emitterA2 = Emitter(EMITTERA2);
			emitters.push_back(emitterA2);

			emitterB4 = Emitter(EMITTERB);
			emitters.push_back(emitterB4);

			catPumpkinBoss = Emitter(EMITTERC);
			catPumpkinBoss.start();
			catPumpkinBoss.sys->applyCircularMovement();
			//emitters.push_back(emitterC);

			cout << "emitter size: " << emitters.size() << endl;
			cout << "switched to level 3" << endl;
			break;
		}

		//start emitters
		for (size_t i = 0; i < emitters.size(); i++) {
			emitters[i].start();
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
	beatLevelOne = false;
	beatLevelTwo = false;
	allDead = false;
	levelType = Level1;
	playerScore = 0;

	//stop emitters from firing
	
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

	catPumpkinBoss.stop();

}

void InGameScreen::draw()
{
	ofClear(0);

	switch(levelType) {

	case WIN:
		ofDrawBitmapString("YOU WIN",  ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 150);
		ofDrawBitmapString("YOUR SCORE: " + to_string(playerScore), ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 130);

		for (int i = 0; i < 7; i++) {
			ofDrawBitmapString(scores[i], ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - i * 20);
		}

		ofDrawBitmapString("Q to go back to menu", ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 + -80);
		break;
	case LOSE:
		ofDrawBitmapString("YOU LOSE", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2 - 150);
		ofDrawBitmapString("YOUR SCORE: " + to_string(playerScore), ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 110);

		ofDrawBitmapString("HIGH SCORES: ", ofGetWindowWidth() / 2 - 75, ofGetWindowHeight() / 2 - 40);
		if (scores.size() > 0) {
			for (int i = 0; i < scores.size() && i < 7; i++) {
				ofDrawBitmapString(scores[i], ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 20 + i * 20);
			}
		}

		ofDrawBitmapString("Q to go back to menu", ofGetWindowWidth() -200, ofGetWindowHeight() -20);
		break;
	default:
		//draw background image
		/*background.resize(ofGetWindowWidth(), ofGetWindowHeight());
		background.draw(0, 0);*/

		ofDrawBitmapString("HP: " + to_string(gunEmitter.hp), 20, 20);
		ofDrawBitmapString("SCORE: " + to_string(playerScore), 20, 40);
		switch (levelType) {
		case Level1:
			if (!beatLevelOne) {
				ofDrawBitmapString("LEVEL 1", 20, ofGetWindowHeight() - 20);
				ofDrawBitmapString("Q to quit, SPACE to fire", ofGetWindowWidth() - 220, ofGetWindowHeight() - 20);
			}
			else {
				ofDrawBitmapString("S to continue onto level 2", ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 150);
			}
			break;
		case Level2:
			if (!beatLevelTwo) {
				ofDrawBitmapString("LEVEL 2", 20, ofGetWindowHeight() - 20);
				ofDrawBitmapString("Q to quit, SPACE to fire", ofGetWindowWidth() - 220, ofGetWindowHeight() - 20);
			}
			else if (beatLevelTwo) {
				ofDrawBitmapString("S to continue onto level 3", ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2 - 150);
			}
			break;
		case Level3:
			if (catPumpkinBoss.emitting == true) {
				catPumpkinBoss.draw();
			}
			ofDrawBitmapString("LEVEL 3", 20, ofGetWindowHeight() - 20);
			ofDrawBitmapString("Q to quit, SPACE to fire", ofGetWindowWidth() - 220, ofGetWindowHeight() - 20);
			break;
		}
		//draw gun
		gunEmitter.draw();

		//draw all enemy emitters
		for (size_t i = 0; i < emitters.size(); i++) {
			if (emitters[i].emitting == true) {
				emitters[i].draw();
			}
		}
		//draw particlesystem for collisions
		pe->draw();

		break;
	}

	


};

void InGameScreen::update() {
	if (levelType != WIN || LOSE) {
		//update gun
		gunEmitter.update();

		//update enemy emitters
		for (int i = 0; i < emitters.size(); i++) {
			if (emitters[i].emitterType == EMITTERB) {
				emitters[i].update(i);
			}
			else {
				emitters[i].update();
			}
			if (emitters[i].spritesFollowGun) {
				emitters[i].velocity = gunEmitter.trans - emitters[i].trans;
			}
		}

		removeDeadEmitters();

		//check if bullets hit enemy sprites
		checkCollisions();

		switch (levelType) {

		case Level1:
			if (!beatLevelOne && allDead) {
				beatLevelOne = true;
				winSound.play();
			}

			break;
		case Level2:
			
			if (allDead && !beatLevelTwo) {
				beatLevelTwo = true;
				winSound.play();
			}

			break;
		case Level3:
			catPumpkinBoss.update();
			if (catPumpkinBoss.hp <= 0) {
				playerScore += 1000;
				winSound.play();
				sort(scores.begin(), scores.end(), greater<float>());
				scores.push_back(playerScore);
				setLevel(WIN);
				
			}
			break;
		}

		//if hp hits 0 or below, transition the screen to home
		if (gunEmitter.hp <= 0) {
			loseSound.play();
			scores.push_back(playerScore);
			sort(scores.begin(), scores.end(), greater<float>());
			setLevel(LOSE);
		}

		pe->update();
	}

	

};

void InGameScreen::checkCollisions() {

	switch (levelType) {
	case Level3:
		catPumpkinBoss.checkCollision(gunEmitter.sys);
		gunEmitter.checkCollision(catPumpkinBoss.sys);
		gunEmitter.checkCollision(catPumpkinBoss);
		playerScore += gunEmitter.sys->checkCollisions(catPumpkinBoss.sys, pe);
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

void InGameScreen::removeDeadEmitters() {
	if (emitters.size() == 0) {
		allDead = true;
		return;
	}
	else {
		vector<Emitter>::iterator e = emitters.begin();
		vector <Emitter>::iterator tmp;

		// check which sprites have <=0 health and delete
		while (e != emitters.end()) {
			if (e->hp <= 0) {
				//          cout << "deleting sprite: " << s->name << endl;
				if (e->emitterType == EMITTERA) {
					playerScore += 100;
				}
				else if (e->emitterType == EMITTERB) {
					playerScore += 300;
				}
				tmp = emitters.erase(e);
				e = tmp;

				//give player 100 pts
				
			}
			else e++;
		}
	}
}

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

		if (beatLevelOne && !beatLevelTwo) {
			cout << "switching to level 2" << endl;
			setLevel(2);
		}

		else if (beatLevelTwo) {
			setLevel(3);
			cout << "switching to level 3" << endl;

		}

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

void InGameScreen::addEnemies() {
	addedEnemies = true;
	emitterA = Emitter(EMITTERA);
	emitters.push_back(emitterA);
	emitterA2 = Emitter(EMITTERA2);
	emitters.push_back(emitterA2);
};