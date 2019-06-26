#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
	glm::dvec3 axisX = glm::dvec3(1.0f, 0.0f, 0.0f);
	glm::dvec3 axisY = glm::dvec3(0.0f, 1.0f, 0.0f);
	glm::dvec3 axisZ = glm::dvec3(0.0f, 0.0f, 1.0f);
public:
	Camera();
	Camera(double cameraPosX, double cameraPosY, double cameraPosZ,
		   double referencePosX, double referencePosY, double referencePosZ,
		   double desiredUp, double desiredUpY, double desiredUpZ);
	Camera(glm::dvec3 cameraPos, glm::dvec3 referencePos, glm::dvec3 desiredUp);

	glm::dmat4 getViewMatrix();
	void updateViewMatrix();

	void setCameraPos(glm::dvec3 position);
	void setCameraPos(double x, double y, double z);
	void setReferencePos(glm::dvec3 position);
	void setReferencePos(double x, double y, double z);
	void setDesiredUp(glm::dvec3 direction);
	void setDesiredUp(double x, double y, double z);

	void move(double delta, double angle = 0);
	void moveUp(double delta);
	void moveCamera(double delta, double angle = 0);
	void moveCameraUp(double delta);
	void moveReference(double delta, double angle = 0);
	void moveReferenceUp(double delta);

	void rotate(double yaw, double pitch, double roll);

private:
	void lookAtReference();
	glm::dvec3 calculateDirection(double angle);
	glm::dvec3 getCameraPos(const glm::dmat4& matrix);

	glm::dvec3 _cameraPos;
	glm::dvec3 _referencePos;
	glm::dvec3 _desiredUp;

	glm::dquat _orientation;
	glm::dmat4 _viewMatrix;
	bool freeMode;
};

//class Camera {
//	glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
//	glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::vec3 axisZ = glm::vec3(0.0f, 0.0f, 1.0f);
//public:
//	Camera();
//	Camera(float cameraPosX, float cameraPosY, float cameraPosZ,
//		   float referencePosX, float referencePosY, float referencePosZ,
//		   float upDirectionX, float upDirectionY, float upDirectionZ);
//	Camera(glm::vec3 cameraPos, glm::vec3 referencePos, glm::vec3 upDirection);
//
//	glm::mat4 getViewMatrix();
//	void updateViewMatrix();
//
//	void setCameraPos(glm::vec3 position);
//	void setCameraPos(float x, float y, float z);
//	void setReferencePos(glm::vec3 position);
//	void setReferencePos(float x, float y, float z);
//	void setUpDirection(glm::vec3 direction);
//	void setUpDirection(float x, float y, float z);
//
//	//void lookAt();
//
//	void move(float delta, float angle = 0);
//	void moveUp(float delta);
//	void moveCamera(float delta, float angle = 0);
//	void moveCameraUp(float delta);
//	void moveReference(float delta, float angle = 0);
//	void moveReferenceUp(float delta);
//
//	void rotate(float yaw, float pitch, float roll);
//
//private:
//	glm::vec3 calculateDirection(float angle);
//	glm::vec3 getCameraPos(const glm::mat4& matrix);
//
//	glm::vec3 _cameraPos;
//	glm::vec3 _referencePos;
//	glm::vec3 _upDirection;
//
//	glm::mat4 _viewMatrix;
//};