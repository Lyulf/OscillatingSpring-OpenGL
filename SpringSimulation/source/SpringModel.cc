#include "SpringSimulation/SpringModel.hh"
#include <glm/gtc/matrix_transform.hpp>

SpringModel::SpringModel(const std::size_t& springStacks, const std::size_t& springSlices,
						 const std::size_t& sphereStacks, const std::size_t& sphereSlices)
	: Model(), _springStacks(springStacks), _springSlices(springSlices),
			   _sphereStacks(sphereStacks), _sphereSlices(sphereSlices) {

	const float minSpringLength = 0.6f * maxSpringLength;
	const float sphereRadius = 5;
	const float connectionSphereRadius = 1;

	const Texture textureSpring("textures/net.jpg");
	const Texture textureSphere("textures/silver.jpg");
	const Texture textureCuboid("textures/white-oak.jpg");

	Mesh cuboid = generateCuboid(textureCuboid, 10, 10, 6, glm::vec3(0, 0, -5));
	Mesh spring = generateSpring(textureSpring);
	Mesh sphere = generateSphere(textureSphere, sphereRadius, glm::vec3(0, 0, minSpringLength + sphereRadius + 2), glm::vec3(0, 0, maxSpringLength + sphereRadius + 2));


	Mesh springStartConnection0 = generateSphere(textureSpring, connectionSphereRadius);
	Mesh springStartConnection1 = generateSphere(textureSpring, connectionSphereRadius, glm::vec3(3, 0, 0));
	Mesh springEndConnection0 = generateSphere(textureSpring, connectionSphereRadius, glm::vec3(3, 0, minSpringLength), glm::vec3(3, 0, maxSpringLength));
	Mesh springEndConnection1 = generateSphere(textureSpring, connectionSphereRadius, glm::vec3(0, 0, minSpringLength), glm::vec3(0, 0, maxSpringLength));

	Mesh cuboidSphereConnection = generateCylinder(textureSpring, connectionSphereRadius, glm::vec3(0, 0, -4), glm::vec3(0, 0, 0));
	Mesh sphereSpringConnection = generateCylinder(textureSpring, connectionSphereRadius, glm::vec3(0, 0, 0), glm::vec3(3, 0, 0));
	Mesh springSphereConnection = generateCylinder(textureSpring, connectionSphereRadius, glm::vec3(3, 0, minSpringLength), glm::vec3(0, 0, minSpringLength), glm::vec3(0, 0, maxSpringLength - minSpringLength));
	Mesh sphereSphereConnection = generateCylinder(textureSpring, connectionSphereRadius, glm::vec3(0, 0, minSpringLength), glm::vec3(0, 0, minSpringLength + sphereRadius + 2), glm::vec3(0, 0, maxSpringLength - minSpringLength));
	_meshes.push_back(cuboid);
	_meshes.push_back(spring);
	_meshes.push_back(sphere);
	_meshes.push_back(springStartConnection0);
	_meshes.push_back(springStartConnection1);
	_meshes.push_back(springEndConnection0);
	_meshes.push_back(springEndConnection1);
	_meshes.push_back(cuboidSphereConnection);
	_meshes.push_back(sphereSpringConnection);
	_meshes.push_back(springSphereConnection);
	_meshes.push_back(sphereSphereConnection);
}

Mesh SpringModel::generateSphere(Texture texture, float radius, glm::vec3 origin) {
	return generateSphere(texture, radius, origin, origin);
}

Mesh SpringModel::generateSphere(Texture texture, float radius, glm::vec3 origin, glm::vec3 destination) {
	// vertices
	Mesh::VertexVector vertices;
	vertices.reserve(_sphereStacks * _sphereSlices);
	for(std::size_t i = 0; i < _sphereStacks; i++) {
		float t = M_PI * i / _sphereStacks;
		for(std::size_t j = 0; j < _sphereSlices; j++) {
			float u = 2.0f * M_PI * j / (_sphereSlices - 1);
			Vertex vertex;
			vertex.position.x = radius * sin(u) * sin(t);
			vertex.position.y = radius * cos(t);
			vertex.position.z = radius * cos(u) * sin(t);
			vertex.textureCoordinates.x = static_cast<float>(j) / (_sphereSlices - 1);
			vertex.textureCoordinates.y = static_cast<float>(_sphereStacks - i - 1) / (_sphereStacks - 1);
			vertex.nextPosition = vertex.position;
			
			vertex.position += origin;
			vertex.nextPosition += destination;
			vertices.push_back(vertex);
		}
	}

	// indices
	Mesh::IndexVector indices;
	indices.reserve(4 * (_sphereStacks - 1) * (_sphereSlices - 1));
	for(std::size_t i = 0; i < _sphereStacks - 1; i++) {
		for(std::size_t j = 0; j < _sphereSlices - 1; j++) {
			indices.push_back(i * _sphereSlices + j);
			indices.push_back((i + 1) * _sphereSlices + j);
			indices.push_back((i + 1) * _sphereSlices + (j + 1));
			indices.push_back(i * _sphereSlices + (j + 1));
		}
	}
	// textures
	Mesh::TextureVector textures;
	textures.push_back(texture);
	return Mesh(vertices, indices, textures);
}

Mesh SpringModel::generateSpring(Texture texture, glm::vec3 origin) {
	return generateSpring(texture, origin, origin);
}

Mesh SpringModel::generateSpring(Texture texture, glm::vec3 origin, glm::vec3 destination) {
	// vertices
	Mesh::VertexVector vertices;
	vertices.reserve(_springStacks * _springSlices);
	for (std::size_t i = 0; i < _springStacks; i++) {
		float t = maxSpringLength * i / _springStacks;
		for (std::size_t j = 0; j < _springSlices; j++) {
			float u = 2 * M_PI * j / (_springSlices - 1);
			
			Vertex vertex;

			vertex.position.x = vertex.nextPosition.x = cos(t) * (3 + cos(u));
			vertex.position.y = vertex.nextPosition.y = sin(t) * (3 + cos(u));
			vertex.position.z = 0.6f * t + sin(u);
			vertex.normal.x = vertex.nextNormal.x = 0;
			vertex.normal.y = vertex.nextNormal.y = 0;
			vertex.normal.z = vertex.nextNormal.z = 0;
			vertex.nextPosition.z = t + sin(u);
			vertex.textureCoordinates.x = static_cast<float>(i) / (_springStacks - 1);
			vertex.textureCoordinates.y = static_cast<float>(j) / (_springSlices - 1);

			vertex.position += origin;
			vertex.nextPosition += destination;
			vertices.push_back(vertex);
		}
	}
	// indices
	Mesh::IndexVector indices;
	indices.reserve(4 * (_springStacks - 1) * (_springSlices - 1));
	for(std::size_t i = 0; i < _springStacks - 1; i++) {
		for(std::size_t j = 0; j < _springSlices - 1; j++) {
			indices.push_back(i * _springSlices + j);
			indices.push_back((i + 1) * _springSlices + j);
			indices.push_back((i + 1) * _springSlices + j + 1);
			indices.push_back(i * _springSlices + j + 1);
		}
	}
	// textures
	Mesh::TextureVector textures;
	textures.push_back(texture);
	return Mesh(vertices, indices, textures);
}

Mesh SpringModel::generateCuboid(Texture texture, float sizeX, float sizeY, float sizeZ, glm::vec3 origin) {
	return generateCuboid(texture, sizeX, sizeY, sizeZ, origin, origin);
}

Mesh SpringModel::generateCuboid(Texture texture, float sizeX, float sizeY, float sizeZ, glm::vec3 origin, glm::vec3 destination) {
	Mesh::VertexVector vertices;
	Mesh::IndexVector indices;
	Mesh::TextureVector textures;
	
	// vertices
	const float hsx = sizeX / 2; // halfWidth
	const float hsy = sizeY / 2; //halfHeight
	const float hsz = sizeZ / 2; // halfLength

	glm::vec3 point0 = glm::vec3(-hsx, -hsy, -hsz);
	glm::vec3 point1 = glm::vec3(hsx, -hsy, -hsz);
	glm::vec3 point2 = glm::vec3(hsx, hsy, -hsz);
	glm::vec3 point3 = glm::vec3(-hsx, hsy, -hsz);
	glm::vec3 point4 = glm::vec3(-hsx, -hsy, hsz);
	glm::vec3 point5 = glm::vec3(hsx, -hsy, hsz);
	glm::vec3 point6 = glm::vec3(hsx, hsy, hsz);
	glm::vec3 point7 = glm::vec3(-hsx, hsy, hsz);
	
	glm::vec3 points[][4] = {
		{point0, point4, point7, point3}, // left
		{point5, point1, point2, point6}, // right
		{point0, point1, point5, point4}, // down
		{point6, point2, point3, point7}, // up
		{point1, point0, point3, point2}, // back
		{point4, point5, point6, point7} // front
	};

	glm::vec3 left = glm::vec3(-1, 0, 0);
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 down = glm::vec3(0, -1, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 back = glm::vec3(0, 0, -1);
	glm::vec3 front = glm::vec3(0, 0, 1);

	glm::vec3 normals[] = {
		left, right, down, up, back, front
	};

	for(std::size_t i = 0; i < 6; i++) {
		for(std::size_t j = 0; j < 4; j++) {
			Vertex vertex;
			vertex.position = points[i][j] + origin;
			vertex.normal = normals[i];
			vertex.textureCoordinates = glm::vec2((j / 2) ^ (j % 2), j / 2);
			vertex.nextPosition = points[i][j] + destination;
			vertex.nextNormal = vertex.normal;

			vertices.push_back(vertex);
		}
	}


	// indices
	for(std::size_t i = 0; i < 4 * 6; i++) {
		indices.push_back(i);
	}

	textures.push_back(texture);

	return Mesh(vertices, indices, textures);
}
#include <iostream>
Mesh SpringModel::generateCylinder(Texture texture, float radius, glm::vec3 start, glm::vec3 end, glm::vec3 delta) {
	// vertices
	const glm::vec3 direction = glm::normalize(end - start);
	const glm::vec3 upDirection = direction != glm::vec3(0.0f, 1.0f, 0.0f) ? glm::vec3(0.0f, 1.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f);
	const glm::vec3 right = glm::normalize(glm::cross(direction, upDirection));

	const glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 axisZ = glm::vec3(0.0f, 0.0f, 1.0f);


	Mesh::VertexVector vertices;
	vertices.reserve(2 * _sphereSlices);
	for(std::size_t i = 0; i < _sphereSlices; i++) {
		float u = 2 * M_PI * i / (_sphereSlices - 1);
		Vertex vertex;
		// start
		vertex.position.x = radius * glm::dot(right, axisX);
		vertex.position.y = radius * glm::dot(right, axisY);
		vertex.position.z = radius * glm::dot(right, axisZ);
		vertex.normal = glm::normalize(vertex.position);
		vertex.position = glm::rotate(glm::mat4(1.0f), u, direction) * glm::vec4(vertex.position, 1.0f);
		vertex.position += start;
		vertex.normal = vertex.nextNormal = glm::rotate(glm::mat4(1.0f), u, direction) * glm::vec4(vertex.normal, 1.0f);
		vertex.textureCoordinates.x = static_cast<float>(i) / (_sphereSlices - 1);
		vertex.textureCoordinates.y = 0.0f;
		vertex.nextPosition = vertex.position;
		vertex.nextPosition += delta;

		vertices.push_back(vertex);
		// end
		vertex.position += end - start;
		vertex.textureCoordinates.y = 1.0f;
		vertex.nextPosition = vertex.position;

		vertex.nextPosition += delta;
		vertices.push_back(vertex);
	}
	// indices
	Mesh::IndexVector indices;
	indices.reserve(4 * 2 * (_sphereSlices - 1));
	for(std::size_t i = 0; i < 2 * (_sphereSlices - 1); i += 2) {
		indices.push_back(i);
		indices.push_back(i + 2);
		indices.push_back(i + 3);
		indices.push_back(i + 1);
	}
	// textures
	Mesh::TextureVector textures;
	textures.push_back(texture);

	return Mesh(vertices, indices, textures);
}