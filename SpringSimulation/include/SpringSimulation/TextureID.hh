#pragma once

class TextureID {
public:
	TextureID(const unsigned int& ID);
	~TextureID();

	unsigned int getID();

private:
	unsigned int _ID;
};