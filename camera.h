#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <gl/glew/glew.h>
#include<gl\glm\glm.hpp>


class Camera {
public:

#pragma region Constructors

	Camera() {

	}

	Camera(glm::vec3 position, float width, float height)
	{
		_position = position;
		_arWidth = width;
		_arHeight = height;
	}

#pragma endregion

#pragma region Operators Overloading

	Camera& operator=(const Camera& cam) {
		_position = cam._position;
		_arWidth = cam._arWidth;
		_arHeight = cam._arHeight;
		return *this;
	}

#pragma endregion

#pragma region Functions

	void UpdatePitch(float pitch) {
		float angle = glm::clamp(pitch, -89.f, 89.f);
		_pitch = _pitch + ((angle * M_PI) / 180.f);
		_updateVectors();
	}

	void UpdateYaw(float yaw) {
		float angle = glm::clamp(yaw, -10.f, 10.f);
		_yaw = _yaw + ((angle * float(M_PI)) / 180.f);
		_updateVectors();
	}

#pragma endregion

#pragma region Accessors
	glm::vec3& Position = _position;
	const glm::vec3& Front = _front;
	const glm::vec3& Up = _up;
	const glm::vec3& Right = _right;
	const float& Pitch = ((_pitch * 180.f) / float(M_PI));
	const float& Yaw = ((_yaw * 180.f) / float(M_PI));
	const float& FOV = ((_fov * 180.f) / float(M_PI));
#pragma endregion

#pragma region World to View Matrices

	glm::mat4 LookAtMat() {
		return glm::lookAt(Position, Position + Front, Up);
	}
	glm::mat4 ProjectionMat() {
		return glm::perspectiveFov(((_fov * 180.f) / float(M_PI)), _arWidth, _arHeight, 0.1f, 100.f);
	}

#pragma endregion
	
private:

#pragma region Member Variables
	
	glm::vec3 _front = glm::vec3(0, 0, -1);
	glm::vec3 _up = glm::vec3(0, 1, 0);
	glm::vec3 _right = glm::vec3(1, 0, 0);
	glm::vec3 _position;
	float     _arWidth;
	float     _arHeight;
	float     _pitch = M_PI;
	float     _yaw = M_PI / 2.f;
	float     _fov = M_PI / 2.f;


#pragma endregion

#pragma region Private Functions

	void _updateVectors() {

		_front = glm::vec3(cosf(_pitch) * cosf(_yaw), 
						   sinf(_pitch),
						   cosf(_pitch) * sinf(_yaw));

		_right = glm::normalize(glm::cross(_front, glm::vec3(0.f, 1.f, 0.f)));
		_up = glm::normalize(glm::cross(_right, _front));
	}

#pragma endregion


};