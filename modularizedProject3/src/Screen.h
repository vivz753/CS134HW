#pragma once
typedef enum { HOME, SELECTLEVEL, INGAME, WIN, LOSE } ScreenType;

class Screen {
public:
	ScreenType type;
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void keyPressed(int) = 0;
	/*void draw();
	void init();
	void update();*/
};