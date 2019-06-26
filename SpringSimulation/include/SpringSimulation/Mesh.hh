#pragma once

#include <vector>
#include "SpringSimulation/Vertex.hh"
#include "SpringSimulation/Texture.hh"
#include "SpringSimulation/Shader.hh"

class Mesh {
public:
	typedef std::vector<Vertex> VertexVector;
	typedef	std::vector<unsigned int> IndexVector;
	typedef	std::vector<Texture> TextureVector;

	Mesh(VertexVector vertices, IndexVector indices, TextureVector textures);

	void draw(Shader shader);

private:
	void setupMesh();

	unsigned int _vertexArray, _vertexBuffer, _elementBuffer;
	VertexVector _vertices;
	IndexVector _indices;
	TextureVector _textures;
};