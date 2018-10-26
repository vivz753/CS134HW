#include "InGameScreen.h"



InGameScreen::InGameScreen(LevelName lname) {
	levelName = lname;
	init();

};

void InGameScreen::init()
{

	switch (levelName) {
	case Level1:

		break;
	case Level2:
		break;
	case Level3:
		break;
	}
	type = INGAME;
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("gotmenu.jpg");

	//load starting bg music
	bgMusic.load("gottheme.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
};

void InGameScreen::draw()
{
	//draw background image
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);
	text.drawString("press spacebar to begin", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);

	//ofClear(0);
	//ofDrawBitmapString("Hello World!", 100, 100);
};

void InGameScreen::update() {
	//cout << "level screen updating" << endl;
};