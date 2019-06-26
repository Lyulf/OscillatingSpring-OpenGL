#pragma once

#include "SpringSimulation/Input.hh"

class Mouse : public Input<int> {
public:
	Mouse();

	int calculateDeltaX(int newX);
	int calculateDeltaY(int newY);
	
	int getMouseX();
	int getMouseY();

	void setMousePosX(int x);
	void setMousePosY(int y);
	void setMousePos(int x, int y);

private:
	int _mousePos[2];
};