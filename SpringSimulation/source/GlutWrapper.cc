#include "SpringSimulation/GlutWrapper.hh"
#include <stdexcept>

GlutApp* GlutWrapper::_glutAppInstance = nullptr;

void GlutWrapper::setInstance(GlutApp* glutAppInstance) {
	_glutAppInstance = glutAppInstance;
}

void GlutWrapper::clearInstance() {
	_glutAppInstance = nullptr;
}


void GlutWrapper::displayCallback() {
	checkInitialization();
	_glutAppInstance->displayCallback();
}

void GlutWrapper::idleCallback() {
	checkInitialization();
	_glutAppInstance->idleCallback();
}

void GlutWrapper::timerCallback(int value) {
	checkInitialization();
	_glutAppInstance->timerCallback(value);
}

void GlutWrapper::mouseCallback(int button, int state, int x, int y) {
	checkInitialization();
	_glutAppInstance->mouseCallback(button, state, x, y);
}

void GlutWrapper::motionCallback(int x, int y) {
	checkInitialization();
	_glutAppInstance->motionCallback(x, y);
}

void GlutWrapper::passiveMotionCallback(int x, int y) {
	checkInitialization();
	_glutAppInstance->passiveMotionCallback(x, y);
}

void GlutWrapper::keyDownCallback(unsigned char key, int x, int y) {
	checkInitialization();
	_glutAppInstance->keyDownCallback(key, x, y);
}

void GlutWrapper::keyUpCallback(unsigned char key, int x, int y) {
	checkInitialization();
	_glutAppInstance->keyUpCallback(key, x, y);
}

void GlutWrapper::specialDownCallback(int key, int x, int y) {
	checkInitialization();
	_glutAppInstance->specialDownCallback(key, x, y);
}

void GlutWrapper::specialUpCallback(int key, int x, int y) {
	checkInitialization();
	_glutAppInstance->specialUpCallback(key, x, y);
}

void GlutWrapper::checkInitialization() {
	if(_glutAppInstance == nullptr) {
		throw std::logic_error("GlutWrapper is not initialized");
	}
}