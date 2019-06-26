#include "SpringSimulation/Mouse.hh"

Mouse::Mouse() {

}

int Mouse::calculateDeltaX(int newX) {
	int deltaX = newX - getMouseX();
	setMousePosX(newX);
	return deltaX;
}

int Mouse::calculateDeltaY(int newY) {
	int deltaY = newY - getMouseY();
	setMousePosY(newY);
	return deltaY;
}

int Mouse::getMouseX() {
	return _mousePos[0];
}

int Mouse::getMouseY() {
	return _mousePos[1];
}

void Mouse::setMousePosX(int x) {
	_mousePos[0] = x;
}

void Mouse::setMousePosY(int y) {
	_mousePos[1] = y;
}

void Mouse::setMousePos(int x, int y) {
	setMousePosX(x);
	setMousePosY(y);
}