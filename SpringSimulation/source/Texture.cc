#include <GL/glew.h>
#include "SpringSimulation/Texture.hh"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>

Texture::TextureMap Texture::loadedTextures;

Texture::Texture(const std::string& texturePath) {
	const auto& texture = loadedTextures.find(texturePath);
	if(texture != loadedTextures.end()) {
		_ID = texture->second->getID();
	} else {
		loadTexture(texturePath);
	}
}

unsigned int Texture::getID() {
	return _ID;
}

void Texture::loadTexture(const std::string& path) {
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if(nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,  GL_RGB, GL_UNSIGNED_BYTE, data);
		} else if(nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		} else
		std::cout << nrChannels << std::endl;
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(data);
	//glDeleteTextures(1, &_ID);
	loadedTextures.insert(TextureMap::value_type(path, std::make_unique<TextureID>(_ID)));
}