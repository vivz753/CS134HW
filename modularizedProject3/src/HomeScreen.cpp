

#include "HomeScreen.h"


HomeScreen::HomeScreen() {
	init();
};

void HomeScreen::init()
{
	type = HOME;

	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("gotmenu.jpg");

	//load starting bg music
	bgMusic.load("gottheme.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
};

void HomeScreen::draw()
{
	//draw background image
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);
	text.drawString("press spacebar to begin", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
	
	//ofClear(0);
	//ofDrawBitmapString("Hello World!", 100, 100);
};

void HomeScreen::update() {
	//cout << "updating" << endl;
};

void HomeScreen::keyPressed(int key) {
	switch (key) {
	case 'w': 
		cout << "w pressed" << endl;
		break;
	
	}
};