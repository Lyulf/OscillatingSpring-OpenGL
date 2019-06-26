#pragma once

#include <map>
#include <string>
#include <memory>
#include "TextureID.hh"

class Texture {
	typedef std::map<std::string, std::unique_ptr<TextureID>> TextureMap;
public:
	Texture(const std::string& texturePath);

	unsigned int getID();
protected:
	void loadTexture(const std::string& path);
private:
	static TextureMap loadedTextures;
	unsigned int _ID;
};