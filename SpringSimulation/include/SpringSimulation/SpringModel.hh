#pragma once

#include "SpringSimulation/Model.hh"
#define _USE_MATH_DEFINES
#include "math.h"

class SpringModel : public Model {
	const float maxSpringLength = 8.0f * M_PI;
public:
	SpringModel(const std::size_t& springStacks, const std::size_t& springSlices,
				const std::size_t& sphereStacks, const std::size_t& sphereSlices);

private:
	inline Mesh generateSphere(Texture texture, float radius, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));
	inline Mesh generateSpring(Texture texture, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));
	inline Mesh generateCuboid(Texture texture, float width, float height, float length, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));

	Mesh generateSphere(Texture texture, float radius, glm::vec3 origin, glm::vec3 destination);
	Mesh generateSpring(Texture texture, glm::vec3 origin, glm::vec3 destination);
	Mesh generateCuboid(Texture texture, float width, float height, float length, glm::vec3 origin, glm::vec3 destination);
	Mesh generateCylinder(Texture texture, float radius, glm::vec3 start, glm::vec3 end, glm::vec3 delta = glm::vec3(0.0f, 0.0f, 0.0f));

	const std::size_t _springStacks, _springSlices;
	const std::size_t _sphereStacks, _sphereSlices;
};