#include "SpringSimulation/Mesh.hh"
#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <iostream>

Mesh::Mesh(VertexVector vertices, IndexVector indices, TextureVector textures) 
	: _vertices(vertices), _indices(indices), _textures(textures) {
	setupMesh();
}

void Mesh::draw(Shader shader) {
	for (std::size_t i = 0; i < _textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		std::string textureName = "Texture[" + std::to_string(i) + "]";
		shader.setInt(textureName.c_str(), i);
		glBindTexture(GL_TEXTURE_2D, _textures[i].getID());
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(_vertexArray);
	// glPointSize(3.0f);
	// glDrawElements(GL_POINTS, _indices.size(), GL_UNSIGNED_INT, 0);
	glDrawElements(GL_QUADS, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &_vertexArray);
	glGenBuffers(1, &_vertexBuffer);
	glGenBuffers(1, &_elementBuffer);

	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_DYNAMIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));
	// vertex next position
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nextPosition));
	// vertex next normal
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nextNormal));

	glBindVertexArray(0);
}