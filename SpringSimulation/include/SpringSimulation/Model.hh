#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "SpringSimulation/Mesh.hh"

class Model {
public:
	Model();

	virtual void draw(Shader shader);
	glm::dmat4 getModelMatrix();

	void addMesh(const Mesh& mesh);
	void translate(double x, double y, double z);

protected:
	std::vector<Mesh> _meshes;

private:
	glm::dmat4 _modelMatrix;
};