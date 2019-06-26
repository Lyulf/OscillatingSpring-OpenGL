#include "SpringSimulation/GlutApp.hh"
#include "SpringSimulation/GlutWrapper.hh"
#include <stdexcept>
#include <iostream>

bool GlutApp::initialized = false;

GlutApp::GlutApp(int* argc, char** argv, std::string windowName, 
				 const int& windowWidth, const int& windowHeight,
				 const int& windowPosX, const int& windowPosY) 
	: _windowName(windowName),
	  _windowWidth(windowWidth), _windowHeight(windowHeight),
	  _windowPosX(windowPosX), _windowPosY(windowPosY) {
	if(initialized) {
		throw std::logic_error("GlutApp already initialized");
	}

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(_windowWidth, _windowHeight);
	glutInitWindowPosition(_windowPosX, _windowPosY);
	glutCreateWindow(_windowName.c_str());

	//glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialize glew");
	}
	GlutWrapper::setInstance(this);
	glutDisplayFunc(GlutWrapper::displayCallback);
	glutIdleFunc(GlutWrapper::idleCallback);
	glutMouseFunc(GlutWrapper::mouseCallback);
	glutMotionFunc(GlutWrapper::motionCallback);
	glutPassiveMotionFunc(GlutWrapper::passiveMotionCallback);
	glutKeyboardFunc(GlutWrapper::keyDownCallback);
	glutKeyboardUpFunc(GlutWrapper::keyUpCallback);
	glutSpecialFunc(GlutWrapper::specialDownCallback);
	glutSpecialUpFunc(GlutWrapper::specialUpCallback);

	initialized = true;
}

GlutApp::~GlutApp() {
	GlutWrapper::clearInstance();
	initialized = false;
}

void GlutApp::run() {
	if(initialized) {
		glutMainLoop();
	}
}

std::string GlutApp::getWindowName() {
	return _windowName;
}

int GlutApp::getWindowWidth() {
	return _windowWidth;
}

int GlutApp::getWindowHeight() {
	return _windowHeight;
}

int GlutApp::getWindowPosX() {
	return _windowPosX;
}

int GlutApp::getWindowPosY() {
	return _windowPosY;
}

void GlutApp::idleCallback() { }
void GlutApp::timerCallback(int value) { }
void GlutApp::mouseCallback(int button, int state, int x, int y) { }
void GlutApp::motionCallback(int x, int y) { }
void GlutApp::passiveMotionCallback(int x, int y) { }
void GlutApp::keyDownCallback(unsigned char key, int x, int y) { }
void GlutApp::keyUpCallback(unsigned char key, int x, int y) { }
void GlutApp::specialDownCallback(int key, int x, int y) { }
void GlutApp::specialUpCallback(int key, int x, int y) { }