#pragma once

#include <string>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	GLint ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	void setInt(const std::string& variableName, const int& value);
	void setUint(const std::string& variableName, const unsigned int& value);
	void setFloat(const std::string& variableName, const float& value);

	void setVec1(const std::string& variableName, float x);
	void setVec1(const std::string& variableName, const glm::vec4& vector);
	void setVec2(const std::string& variableName, float x, float y);
	void setVec2(const std::string& variableName, const glm::vec4& vector);
	void setVec3(const std::string& variableName, float x, float y, float z);
	void setVec3(const std::string& variableName, const glm::vec4& vector);
	void setVec4(const std::string& variableName, float x, float y, float z, float w);
	void setVec4(const std::string& variableName, const glm::vec4& vector);

	void setMat4(const std::string& variableName, const glm::mat4& matrix);
};

