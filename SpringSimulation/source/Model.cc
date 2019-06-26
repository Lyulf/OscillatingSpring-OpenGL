#include "SpringSimulation/Model.hh"
#include <glm/gtc/matrix_transform.hpp>

Model::Model() 
	: _meshes(), _modelMatrix(1.0f){

}

void Model::draw(Shader shader) {
	for (auto& mesh : _meshes) {
		mesh.draw(shader);
	}
}

glm::dmat4 Model::getModelMatrix() {
	return _modelMatrix;
}

void Model::addMesh(const Mesh& mesh) {
	_meshes.push_back(mesh);
}

void Model::translate(double x, double y, double z) {
	_modelMatrix = glm::translate(_modelMatrix, glm::dvec3(x, y, z));
}