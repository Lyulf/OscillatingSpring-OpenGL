#pragma once

#include "SpringSimulation/GlutApp.hh"

class GlutWrapper {
public:
	static void setInstance(GlutApp* glutAppInstance);
	static void clearInstance();

	static void displayCallback();
	static void idleCallback();
	static void timerCallback(int value);
	static void mouseCallback(int button, int state, int x, int y);
	static void motionCallback(int x, int y);
	static void passiveMotionCallback(int x, int y);
	static void keyDownCallback(unsigned char key, int x, int y);
	static void keyUpCallback(unsigned char key, int x, int y);
	static void specialDownCallback(int key, int x, int y);
	static void specialUpCallback(int key, int x, int y);

private:
	static void checkInitialization();
	static GlutApp* _glutAppInstance;
};