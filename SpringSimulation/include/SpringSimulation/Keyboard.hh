#pragma once

#include "SpringSimulation/Input.hh"

class Keyboard : public Input<unsigned char> {
public:
	Keyboard();

	Input<int> special;
};