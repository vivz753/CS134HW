

#include "HomeScreen.h"


HomeScreen::HomeScreen() {
	screenType = HOME;
	menuType = DEFAULT;
	
};

void HomeScreen::init()
{
	transitionLevel = 1;
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("gotmenu.jpg");

	//load starting bg music
	bgMusic.load("gottheme.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
};

void HomeScreen::terminate() {
	bgMusic.stop();
	transition = false;
	menuType = DEFAULT;
}

void HomeScreen::draw()
{
	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);

	switch (menuType) {
	case DEFAULT:
		text.drawString("press s to start; l to select level", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case SELECTLEVEL:
		text.drawString("press 1 for level1, 2 for level2, 3 for level3", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	}
	//draw background image

	
	//ofClear(0);
	//ofDrawBitmapString("Hello World!", 100, 100);
};

void HomeScreen::update() {
	//cout << "updating" << endl;
};

void HomeScreen::keyPressed(int key) {

	switch (menuType) {
	case DEFAULT:
		switch (key) {
		case 's':
			cout << "start game; transition to INGAME" << endl;
			transitionScreen = INGAME;
			transition = true;
			break;
		case 'l':
			cout << "switch to select level menu" << endl;
			menuType = SELECTLEVEL;
			break;
		}
		break;
	case SELECTLEVEL:
		switch (key) {
		case 'b':
			cout << "back to menu" << endl;
			menuType = DEFAULT;
			break;
		case '1':
			cout << "transition to INGAME, Level1" << endl;
			
			transition = true;
			transitionLevel = 1;
			transitionScreen = INGAME;
			break;
		case '2':
			cout << "transition to INGAME, Level2" << endl;
			
			transition = true;
			transitionLevel = 2;
			transitionScreen = INGAME;
			break;
		case '3':
			cout << "transition to INGAME, Level3" << endl;
			
			transition = true;
			transitionLevel = 3;
			transitionScreen = INGAME;
			break;
		}
		break;
	}

	
};