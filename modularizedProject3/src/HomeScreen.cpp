

#include "HomeScreen.h"


HomeScreen::HomeScreen() {
	screenType = HOME;
	menuType = DEFAULT;
	
};

void HomeScreen::init()
{

	//pe.setPosition(ofVec3f(50,500,0));
	

	//delete laters

	transitionLevel = 1;
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("halloweenmenu.jpg");

	//load starting bg music
	bgMusic.load("halloweenmenu.mp3");
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


	/*background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);*/

	switch (menuType) {
	case DEFAULT:
		ofClear(0);
		ofDrawBitmapString("S to start", ofGetWindowWidth()/2-50, ofGetWindowHeight() / 2);
		ofDrawBitmapString("L to select level", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2 + 20);
		//text.drawString("press s to start; l to select level", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case SELECTLEVEL:
		ofClear(0);
		ofDrawBitmapString("1 for level 1", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2);
		ofDrawBitmapString("2 for level 2", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2 + 20);
		ofDrawBitmapString("3 for level 3", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2 + 40);
		ofDrawBitmapString("B to go back", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2 + 100);
		//text.drawString("press 1 for level1, 2 for level2, 3 for level3", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	}
	//draw background image
	//
	//ofClear(0);
	//
	//	//test
	//pe.draw();
	////delete later

};

void HomeScreen::update() {
	//cout << "updating" << endl;

	//pe.update();
	//delete later
};

void HomeScreen::keyPressed(int key) {

	switch (menuType) {
	case DEFAULT:
		switch (key) {
		case 'a':
			pe.start();
			break;
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

void HomeScreen::keyReleased(int key) {

};

void HomeScreen::mouseMoved(int x, int y) {
	
};

void HomeScreen::mousePressed(int x, int y, int button) {
	
};

void HomeScreen::mouseDragged(int x, int y, int button) {
	
};

void HomeScreen::mouseReleased(int x, int y, int button) {
};