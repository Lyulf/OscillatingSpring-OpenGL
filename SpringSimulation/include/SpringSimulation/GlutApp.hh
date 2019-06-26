#pragma once

#include <GL/glew.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string>

class GlutApp {
public:
	GlutApp(int* argc, char** argv, std::string windowName, 
			const int& windowWidth, const int& windowHeight,
			const int& windowPosX, const int& windowPosY);
	~GlutApp();

	void run();

	std::string getWindowName();
	int getWindowWidth();
	int getWindowHeight();
	int getWindowPosX();
	int getWindowPosY();

private:
	virtual void displayCallback() = 0;
	virtual void idleCallback();
	virtual void timerCallback(int value);
	virtual void mouseCallback(int button, int state, int x, int y);
	virtual void motionCallback(int x, int y);
	virtual void passiveMotionCallback(int x, int y);
	virtual void keyDownCallback(unsigned char key, int x, int y);
	virtual void keyUpCallback(unsigned char key, int x, int y);
	virtual void specialDownCallback(int key, int x, int y);
	virtual void specialUpCallback(int key, int x, int y);

	std::string _windowName;
	int _windowWidth, _windowHeight, _windowPosX, _windowPosY;
	static bool initialized;

	friend class GlutWrapper;
};