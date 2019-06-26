#pragma once

#include "SpringSimulation/GlutApp.hh"
#include "SpringSimulation/Shader.hh"
#include "SpringSimulation/Model.hh"
#include "SpringSimulation/Camera.hh"
#include "SpringSimulation/Mouse.hh"
#include "SpringSimulation/Keyboard.hh"
#include <vector>
#include <glm/glm.hpp>

class Simulation : public GlutApp {
	typedef std::vector<Model> ModelVector;
	const int inputDelay = 10;
	const int fps = 240;
	const float mouseSensitivity = 0.25f;
	const float movementSpeed = 0.05f * inputDelay;
	const float rotationSpeed = 0.05f * inputDelay;

public:
	Simulation(int* argc, char** argv,std::string windowName, 
			   const int& windowWidth, const int& windowHeight,
			   const int& windowPosX, const int& windowPosY);

private:
	enum class Functions : int {
		IDLE,
		DISPLAY,
		HANDLE_INPUTS
	};

	void callFunction(int ms, Functions func);
	void handleInputs();

	void displayCallback();
	void timerCallback(int functionNumber);
	void mouseCallback(int button, int state, int x, int y);
	void motionCallback(int x, int y);
	void keyDownCallback(unsigned char key, int x, int y);
	void keyUpCallback(unsigned char key, int x, int y);
	void specialDownCallback(int key, int x, int y);
	void specialUpCallback(int key, int x, int y);

	Mouse _mouse;
	Keyboard _keyboard;
	Camera _camera;
	ModelVector _models;
	Shader _defaultShader;
	glm::dmat4 _projectionMatrix;
};