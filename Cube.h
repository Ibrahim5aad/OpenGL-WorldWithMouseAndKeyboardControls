#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <gl/glew/glew.h>
#include<gl\glm\glm.hpp>
#include<gl\glm\gtc\type_ptr.hpp>
#include<gl\glm\gtx\transform.hpp>
#include<vector>
#include "vertex.h"
using namespace std;
using namespace glm;

vector<vertex> cube_vertices;
glm::mat4 modelMats[] = {

		glm::translate(glm::vec3(0.f, 0.f, 0.f)) ,
		glm::translate(glm::vec3(2.f, 0.f, 0.f)) ,
		glm::translate(glm::vec3(4.f, 0.f, 0.f)) ,
		glm::translate(glm::vec3(6.f, 0.f, 0.f)) ,

		glm::translate(glm::vec3(0.f, 0.f, -2.f)) ,
		glm::translate(glm::vec3(2.f, 0.f, -2.f)) ,
		glm::translate(glm::vec3(4.f, 0.f, -2.f)) ,
		glm::translate(glm::vec3(6.f, 0.f, -2.f)) ,

		glm::translate(glm::vec3(0.f, 0.f, -4.f)) ,
		glm::translate(glm::vec3(2.f, 0.f, -4.f)) ,
		glm::translate(glm::vec3(4.f, 0.f, -4.f)) ,
		glm::translate(glm::vec3(6.f, 0.f, -4.f)) ,

		glm::translate(glm::vec3(0.f, 0.f, -6.f)) ,
		glm::translate(glm::vec3(2.f, 0.f, -6.f)) ,
		glm::translate(glm::vec3(4.f, 0.f, -6.f)) ,
		glm::translate(glm::vec3(6.f, 0.f, -6.f)) ,


		glm::translate(glm::vec3(1.f, 1.1f, -1.f)),
		glm::translate(glm::vec3(3.f, 1.1f, -1.f)),
		glm::translate(glm::vec3(5.f, 1.1f, -1.f)),

		glm::translate(glm::vec3(1.f, 1.1f, -3.f)),
		glm::translate(glm::vec3(3.f, 1.1f, -3.f)),
		glm::translate(glm::vec3(5.f, 1.1f, -3.f)),

		glm::translate(glm::vec3(1.f, 1.1f, -5.f)),
		glm::translate(glm::vec3(3.f, 1.1f, -5.f)),
		glm::translate(glm::vec3(5.f, 1.1f, -5.f)),

		glm::translate(glm::vec3(2.f, 2.1f, -2.f)),
		glm::translate(glm::vec3(4.f, 2.1f, -2.f)),

		glm::translate(glm::vec3(2.f, 2.1f, -4.f)),
		glm::translate(glm::vec3(4.f, 2.1f, -4.f)),


		glm::translate(glm::vec3(2.f, 3.1f, -2.5f)) * glm::scale(glm::vec3(0.7,0.7,0.7)),
		glm::translate(glm::vec3(4.f, 3.1f, -2.5f)) * glm::scale(glm::vec3(0.7,0.7,0.7)),
		glm::translate(glm::vec3(2.f, 3.1f, -3.5f)) * glm::scale(glm::vec3(0.7,0.7,0.7)),
		glm::translate(glm::vec3(4.f, 3.1f, -3.5f)) * glm::scale(glm::vec3(0.7,0.7,0.7)),

		glm::translate(glm::vec3(3.f, 3.6f, -3.f)) * glm::scale(glm::vec3(2,.2,1.7)),
		glm::translate(glm::vec3(3.f, 3.9f, -3.f)) * glm::scale(glm::vec3(1.5,.2,1.3)),
		glm::translate(glm::vec3(3.f, 4.2f, -3.f)) * glm::scale(glm::vec3(.9,.2,.7)),
		glm::translate(glm::vec3(3.f, 4.5f, -3.f)) * glm::scale(glm::vec3(.7,0.2,.5)),

};

class Cube {
public:
	
	static void	CreateCube() {

		cube_vertices.insert(cube_vertices.end(), {
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)),
				vertex(vec3(0.5f, -0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f),  vec2(1.0f, 0.0f)),
				vertex(vec3(0.5f, 0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f),   vec2(1.0f, 1.0f)),
				vertex(vec3(0.5f, 0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f),   vec2(1.0f, 1.0f)),
				vertex(vec3(-0.5f, 0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f),  vec2(0.0f, 1.0f)),
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)),
																		  
				vertex(vec3(-0.5f, -0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),   vec2(0.0f, 0.0f)),
				vertex(vec3(0.5f, -0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),    vec2(1.0f, 0.0f)),
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),     vec2(1.0f, 1.0f)),
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),     vec2(1.0f, 1.0f)),
				vertex(vec3(-0.5f, 0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),    vec2(0.0f, 1.0f)),
				vertex(vec3(-0.5f, -0.5f, 0.5f),vec3(0.0f, 0.0f, 1.0f),   vec2(0.0f, 0.0f)),
																		  
				vertex(vec3(-0.5f, 0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),   vec2(1.0f, 0.0f)),
				vertex(vec3(-0.5f, 0.5f, -0.5f),vec3(-1.0f, 0.0f, 0.0f),  vec2(1.0f, 1.0f)),
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),
				vertex(vec3(-0.5f, -0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),  vec2(0.0f, 0.0f)),
				vertex(vec3(-0.5f, 0.5f, 0.5f),vec3(-1.0f, 0.0f, 0.0f),   vec2(1.0f, 0.0f)),
																		
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(1.0f, 0.0f, 0.0f),     vec2(1.0f, 0.0f)),
				vertex(vec3(0.5f, 0.5f, -0.5f),vec3(1.0f, 0.0f, 0.0f),    vec2(1.0f, 1.0f)),
				vertex(vec3(0.5f, -0.5f, -0.5f),vec3(1.0f, 0.0f, 0.0f),   vec2(0.0f, 1.0f)),
				vertex(vec3(0.5f, -0.5f, -0.5f),vec3(1.0f, 0.0f, 0.0f),   vec2(0.0f, 1.0f)),
				vertex(vec3(0.5f, -0.5f, 0.5f),vec3(1.0f, 0.0f, 0.0f),    vec2(0.0f, 0.0f)),
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(1.0f, 0.0f, 0.0f),     vec2(1.0f, 0.0f)),
																		
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(.0f, -1.0f, 0.0f),  vec2(0.0f, 1.0f)),
				vertex(vec3(0.5f, -0.5f, -0.5f),vec3(0.0f, -1.0f, 0.0f),  vec2(1.0f, 1.0f)),
				vertex(vec3(0.5f, -0.5f, 0.5f),vec3(0.0f, -1.0f, 0.0f),   vec2(1.0f, 0.0f)),
				vertex(vec3(0.5f, -0.5f, 0.5f),vec3(0.0f, -1.0f, 0.0f),   vec2(1.0f, 0.0f)),
				vertex(vec3(-0.5f, -0.5f, 0.5f),vec3(0.0f, -1.0f, 0.0f),  vec2(0.0f, 0.0f)),
				vertex(vec3(-0.5f, -0.5f, -0.5f),vec3(.0f, -1.0f, 0.0f),  vec2(0.0f, 1.0f)),
																		
				vertex(vec3(-0.5f, 0.5f, -0.5f),vec3(0.0f, 1.0f, 0.0f),   vec2(0.0f, 1.0f)),
				vertex(vec3(0.5f, 0.5f, -0.5f),vec3(0.0f, 1.0f, 0.0f),    vec2(1.0f, 1.0f)),
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(0.0f, 1.0f, 0.0f),     vec2(1.0f, 0.0f)),
				vertex(vec3(0.5f, 0.5f, 0.5f),vec3(0.0f, 1.0f, 0.0f),     vec2(1.0f, 0.0f)),
				vertex(vec3(-0.5f, 0.5f, 0.5f),vec3(0.0f, 1.0f, 0.0f),    vec2(0.0f, 0.0f)),
				vertex(vec3(-0.5f, 0.5f, -0.5f),vec3(0.0f, 1.0f, 0.0f),   vec2(0.0f, 1.0f))
			});
		glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(vertex), cube_vertices.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(vec3)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(vec3)));
		glEnableVertexAttribArray(1);


	}
	static void CubeTransformationMatsData() {

		glBufferData(GL_ARRAY_BUFFER, sizeof(modelMats), modelMats, GL_STATIC_DRAW);

		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));

		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}

};