#pragma once
#include<gl\glm\glm.hpp>

using namespace std;
using namespace glm;

struct vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;

public:

	vertex() = default;

	vertex(vec3 _position) :position{ _position }, normal(0, 0, 0){

	}

	vertex(vec3 pos, vec3 norm, vec2 text) {

		position = pos;
		normal = norm;
		texture = text;
	}
};