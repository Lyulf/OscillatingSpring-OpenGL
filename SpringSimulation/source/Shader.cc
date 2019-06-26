#include "SpringSimulation/Shader.hh"
#include <fstream>
#include <iostream>
#include <sstream>

std::string loadSourceCode(const GLchar* path);
int compileShader(unsigned int shader, const char* code);
int linkProgram(GLint program, unsigned int vertexShader, unsigned int fragmentShader);

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexCode, fragmentCode;
	
	try {
		vertexCode = loadSourceCode(vertexPath);
	} catch(std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	try {
		fragmentCode = loadSourceCode(fragmentPath);
	} catch(std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	success = compileShader(vertex, vertexShaderCode);

	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	if(!success) {
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
	}
	if(strlen(infoLog)) {
		std::cout << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	success = compileShader(fragment, fragmentShaderCode);

	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	if(!success) {
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
	}
	if(strlen(infoLog)) {
		std::cout << infoLog << std::endl;
	}

	ID = glCreateProgram();
	success = linkProgram(ID, vertex, fragment);

	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	if(!success) {
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
	}
	if(strlen(infoLog)) {
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

std::string loadSourceCode(const GLchar* path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(path);
	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

int compileShader(unsigned int shader, const char* code) {
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success;
}

int linkProgram(GLint program, unsigned int vertexShader, unsigned int fragmentShader) {
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	return success;
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setInt(const std::string& variable, const int& value) {
	glUniform1i(glGetUniformLocation(ID, variable.c_str()), value);
}

void Shader::setUint(const std::string& variable, const unsigned int& value) {
	glUniform1ui(glGetUniformLocation(ID, variable.c_str()), value);
}

void Shader::setFloat(const std::string& variable, const float& value) {
	glUniform1f(glGetUniformLocation(ID, variable.c_str()), value);
}

void Shader::setVec1(const std::string& variable, float x) {
	glUniform1f(glGetUniformLocation(ID, variable.c_str()), x);
}

void Shader::setVec1(const std::string& variable, const glm::vec4& vector) {
	glUniform1fv(glGetUniformLocation(ID, variable.c_str()), 1, &vector[0]);
}

void Shader::setVec2(const std::string& variable, float x, float y) {
	glUniform2f(glGetUniformLocation(ID, variable.c_str()), x, y);
}

void Shader::setVec2(const std::string& variable, const glm::vec4& vector) {
	glUniform2fv(glGetUniformLocation(ID, variable.c_str()), 1, &vector[0]);
}

void Shader::setVec3(const std::string& variable, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(ID, variable.c_str()), x, y, z);
}

void Shader::setVec3(const std::string& variable, const glm::vec4& vector) {
	glUniform3fv(glGetUniformLocation(ID, variable.c_str()), 1, &vector[0]);
}

void Shader::setVec4(const std::string& variable, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(ID, variable.c_str()), x, y, z, w);
}

void Shader::setVec4(const std::string& variable, const glm::vec4& vector) {
	glUniform4fv(glGetUniformLocation(ID, variable.c_str()), 1, &vector[0]);
}


void Shader::setMat4(const std::string& variable, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(ID, variable.c_str()), 1, GL_FALSE, &matrix[0][0]);
}
