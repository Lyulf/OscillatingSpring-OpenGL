#include "SpringSimulation/Simulation.hh"
#include "SpringSimulation/GlutWrapper.hh"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "SpringSimulation/SpringModel.hh"
#include <stb/stb_image.h>
#include <chrono>
#include <thread>

Simulation::Simulation(int* argc, char** argv, std::string windowName, 
					   const int& windowWidth, const int& windowHeight,
					   const int& windowPosX, const int& windowPosY)
	: GlutApp(argc, argv,
			  windowName,
			  windowWidth, windowHeight,
			  windowPosX, windowPosY),
	  _mouse(), _keyboard(), _camera(), _models(),
	  _defaultShader("shaders/KeyFrameAnimation.vs.glsl",
					 "shaders/Texture.fs.glsl") {
	_projectionMatrix = glm::perspective(90.0f, static_cast<float>(windowWidth) / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	_models.push_back(SpringModel(418, 83, 187, 187));
	glClearColor(181.0f / 255, 211.0f / 255, 231.0f / 255, 1.0f);
	callFunction(1, Functions::IDLE);
	callFunction(1, Functions::DISPLAY);
	callFunction(1, Functions::HANDLE_INPUTS);
}

void Simulation::callFunction(int ms, Functions func) {
	glutTimerFunc(ms, GlutWrapper::timerCallback, static_cast<int>(func));
}

void Simulation::handleInputs() {
	if(_keyboard.isPressed('w')) {
		_camera.moveCamera(movementSpeed);
	}
	if(_keyboard.isPressed('s')) {
		_camera.moveCamera(movementSpeed, 180);
	}
	if(_keyboard.isPressed('a')) {
		_camera.moveCamera(movementSpeed, 270);
	}
	if(_keyboard.isPressed('d')) {
		_camera.moveCamera(movementSpeed, 90);
	}
	if(_keyboard.isPressed('q')) {
		_camera.rotate(0, 0, rotationSpeed);
	}
	if(_keyboard.isPressed('e')) {
		_camera.rotate(0, 0, -rotationSpeed);
	}
	if(_mouse.isPressed()) {
		int newX = getWindowWidth() / 2;
		int newY = getWindowHeight() / 2;
		int mouseDeltaX = _mouse.calculateDeltaX(newX) * mouseSensitivity;
		int mouseDeltaY = _mouse.calculateDeltaY(newY) * mouseSensitivity;
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(newX, newY);
		_mouse.setMousePos(newX, newY);

		if(_mouse.isPressed(GLUT_LEFT_BUTTON)) {
			float yaw = mouseDeltaX;
			float pitch = -mouseDeltaY;
			_camera.rotate(yaw, 0, 0);
			_camera.rotate(0, pitch, 0);
		}
		if(_mouse.isPressed(GLUT_RIGHT_BUTTON)) {
			_camera.move(mouseDeltaX, 270);
			_camera.moveUp(mouseDeltaY);
		}
	} else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	_camera.updateViewMatrix();
}

void Simulation::displayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const int period = 1000;
	static const float angularFreq = 2.0f * M_PI / period;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float tweenFactor = (sin(time * angularFreq) + 1.0f) / 2.0f;
	_defaultShader.setFloat("TweenFactor", tweenFactor);
	_defaultShader.use();
	for (auto& model : _models) {
		glm::dmat4 modelViewMatrix = _camera.getViewMatrix() * model.getModelMatrix();
		glm::dmat4 projectionModelViewMatrix = _projectionMatrix * modelViewMatrix;
		_defaultShader.setMat4("ProjectionModelViewMatrix", projectionModelViewMatrix);
		model.draw(_defaultShader);
	}
	glutSwapBuffers();
	glFlush();
}

void Simulation::timerCallback(int functionNumber) {
	switch(static_cast<Functions>(functionNumber)) {
	// reduces cpu usage
	case Functions::IDLE:
		callFunction(4, Functions::IDLE);
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
		break;
	case Functions::DISPLAY:
		callFunction(1000 / fps, Functions::DISPLAY);
		glutPostRedisplay();
		break;
	case Functions::HANDLE_INPUTS:
		callFunction(inputDelay, Functions::HANDLE_INPUTS);
		handleInputs();
		break;
	default:
		break;
	}
}

void Simulation::mouseCallback(int button, int state, int x, int y) {
	const int newX = getWindowWidth() / 2;
	const int newY = getWindowHeight() / 2;
	glutWarpPointer(newX, newY);
	_mouse.setMousePos(newX, newY);
	if(state == GLUT_DOWN) {
		_mouse.press(button);
	} else if(state == GLUT_UP){
		_mouse.release(button);
	}
}

void Simulation::motionCallback(int x, int y) {
	_mouse.setMousePos(x, y);
}

void Simulation::keyDownCallback(unsigned char key, int x, int y) {
	_mouse.setMousePos(x, y);
	_keyboard.press(tolower(key));
}

void Simulation::keyUpCallback(unsigned char key, int x, int y) {
	_mouse.setMousePos(x, y);
	_keyboard.release(tolower(key));
}

void Simulation::specialDownCallback(int key, int x, int y) {
	_mouse.setMousePos(x, y);
	_keyboard.special.press(key);
}

void Simulation::specialUpCallback(int key, int x, int y) {
	_mouse.setMousePos(x, y);
	_keyboard.special.release(key);
}