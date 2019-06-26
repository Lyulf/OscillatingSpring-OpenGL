#include <GL/glew.h>
#include "SpringSimulation/TextureID.hh"
#include <iostream>

TextureID::TextureID(const unsigned int& ID) {
	_ID = ID;
}

TextureID::~TextureID() {
	glDeleteTextures(1, &_ID);
}

unsigned int TextureID::getID() {
	return _ID;
}