#include "InGameScreen.h"


InGameScreen::InGameScreen() {
	
	screenType = INGAME;
	levelType = Level1;
	//init();

};

//InGameScreen::InGameScreen(LevelName lname) {
//	levelName = lname;
//	init();
//
//};

void InGameScreen::setLevel(LevelType level) {
	levelType = level;
};

void InGameScreen::setLevel(int level) {
	switch (level) {
	case 1:
		levelType = Level1;
		break;
	case 2:
		levelType = Level2;
		break;
	case 3:
		levelType = Level3;
		break;
	}
}

void InGameScreen::init()
{

	switch (levelType) {
	case Level1:
		cout << "switched to level 1" << endl;
		break;
	case Level2:
		cout << "switched to level 2" << endl;
		break;
	case Level3:
		cout << "switched to level 3" << endl;
		break;
	}
	
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("northofthewall.jpg");

	//load starting bg music
	bgMusic.load("battle.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
};

void InGameScreen::terminate() {
	bgMusic.stop();
	transition = false;
}

void InGameScreen::draw()
{
	//draw background image

	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);

	switch (levelType) {
	case Level1:
		text.drawString("level 1; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level2:
		text.drawString("level 2; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level3:
		text.drawString("level 3; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	}
	

};

void InGameScreen::update() {
	//if levelType=1 & beat=true, levelType = Level2
	//cout << "level screen updating" << endl;
};

void InGameScreen::keyPressed(int key) {
	switch (key) {
	case ' ':
		cout << "pressing space in game" << endl;
		break;
	case 'q':
		cout << "pressing q in game" << endl;
		transition = true;
		transitionScreen = HOME;
		break;
	}
};