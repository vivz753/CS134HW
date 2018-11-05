#pragma once
typedef enum { HOME, INGAME } ScreenType;

class Screen {
public:
	ScreenType screenType;
	ScreenType transitionScreen;
	bool transition;
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void keyPressed(int) = 0;
	virtual void keyReleased(int) = 0;
	virtual void mouseMoved(int, int) = 0;
	virtual void mousePressed(int, int, int) =0;
	virtual void mouseDragged(int, int, int) =0;
	virtual void mouseReleased(int, int, int) =0;
	//stops music and clears data
	virtual void terminate() = 0;
	/*void draw();
	void init();
	void update();*/
};