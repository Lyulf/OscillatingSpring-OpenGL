#include "SpringSimulation/Camera.hh"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

Camera::Camera()
	: Camera(0, 0, -12, 0, 0, 0, 0, 1, 0) { }

Camera::Camera(double cameraPosX, double cameraPosY, double cameraPosZ,
			   double referencePosX, double referencePosY, double referencePosZ,
			   double desiredUpX, double desiredUpY, double desiredUpZ)
	: Camera(glm::dvec3(cameraPosX, cameraPosY, cameraPosZ),
			 glm::dvec3(referencePosX, referencePosY, referencePosZ),
			 glm::dvec3(desiredUpX, desiredUpY, desiredUpZ)) { }

Camera::Camera(glm::dvec3 cameraPos, glm::dvec3 referencePos, glm::dvec3 desiredUp)
	: _cameraPos(cameraPos), _referencePos(referencePos), _desiredUp(desiredUp),
	  _orientation(1, 0, 0, 0), freeMode(false) {
	updateViewMatrix();
}


glm::dmat4 Camera::getViewMatrix() {
	return _viewMatrix;
}

void Camera::updateViewMatrix() {
	if(!freeMode) {
		lookAtReference();
	}
	glm::dmat4 rotation = glm::mat4_cast(glm::inverse(_orientation));
	_viewMatrix = glm::translate(rotation, -_cameraPos);
}

void Camera::setCameraPos(glm::dvec3 position) {
	_cameraPos = position;
}

void Camera::setCameraPos(double x, double y, double z) {
	setCameraPos(glm::dvec3(x, y, z));
}

void Camera::setReferencePos(glm::dvec3 position) {
	_referencePos = position;
}

void Camera::setReferencePos(double x, double y, double z) {
	setReferencePos(glm::dvec3(x, y, z));
}

void Camera::setDesiredUp(glm::dvec3 up) {
	_desiredUp = glm::normalize(up);
}

void Camera::setDesiredUp(double x, double y, double z) {
	setDesiredUp(glm::dvec3(x, y, z));
}

void Camera::move(double delta, double angle) {
	moveCamera(delta, angle);
	moveReference(delta, angle);
}

void Camera::moveUp(double delta) {
	moveCameraUp(delta);
	moveReferenceUp(delta);
}

void Camera::moveCamera(double delta, double angle) {
	glm::dvec3 direction = calculateDirection(angle);
	_cameraPos += direction * delta;
}

void Camera::moveCameraUp(double delta) {
	_cameraPos += _desiredUp * delta;
}

void Camera::moveReference(double delta, double angle) {
	glm::dvec3 direction = calculateDirection(angle);
	_referencePos += direction * delta;
}

void Camera::moveReferenceUp(double delta) {
	_referencePos += _desiredUp * delta;
}

void Camera::rotate(double yaw, double pitch, double roll) {
	yaw = glm::radians(yaw);
	pitch = glm::radians(pitch);
	roll = glm::radians(roll);
	glm::dvec3 direction = _referencePos - _cameraPos;
	if(glm::length(direction) <= 0.0001) {
		direction = axisZ;
	} else {
		glm::normalize(direction);
	}
	glm::dvec3 right = glm::normalize(glm::cross(direction, _desiredUp));
	glm::dvec3 front = glm::normalize(glm::cross(_desiredUp, right));
	glm::dquat rotation = glm::dquat(1, 0, 0, 0);
	rotation *= glm::angleAxis(-pitch, right);
	rotation *= glm::angleAxis(yaw, axisY);
	rotation *= glm::angleAxis(roll, front);
	rotation = glm::normalize(rotation);
	_cameraPos = _referencePos + (rotation * (_cameraPos - _referencePos) * glm::inverse(rotation));
	_desiredUp = glm::normalize(rotation * _desiredUp * glm::inverse(rotation));
}

void Camera::lookAtReference() {
	glm::dvec3 direction = _referencePos - _cameraPos;
	double directionLength = glm::length(direction);

	if(directionLength <= 0.0001) {
		_orientation = glm::dquat(1, 0, 0, 0);
		return;
	}

	direction = glm::normalize(direction);

	if(glm::abs(glm::dot(direction, _desiredUp)) < 0.9999) {
		_orientation = glm::quatLookAt(direction, _desiredUp);
	} else if(glm::abs(glm::dot(direction, axisY)) < 0.9999) {
		_orientation = glm::quatLookAt(direction, axisY);
	} else {
		_orientation = glm::quatLookAt(direction, axisZ);
	}
}

glm::dvec3 Camera::calculateDirection(double angle) {
	glm::dvec3 direction = glm::normalize(_referencePos - _cameraPos);
	angle = glm::radians(angle);
	return glm::rotate(glm::dmat4(1.0f), -angle, _desiredUp) * glm::dvec4(direction, 1.0f);
}

glm::dvec3 Camera::getCameraPos(const glm::dmat4& matrix) {
	return matrix[3];
}