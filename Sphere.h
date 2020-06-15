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


vector<vertex> sphere_vertices;


vec3 Sphere_Core_vertices[4] = {
	vec3(0.0, 0.0, 1.0),
	vec3(0.0, 0.942809, -0.333333),
	vec3(-0.816497, -0.471405, -0.333333),
	vec3(0.816497, -0.471405, -0.333333)
};




class Sphere
{



	static void Triangle(vec3 a, vec3 b, vec3 c)
	{
		// flat shading
		vec3 normal = cross((c - a), (b - a));
		sphere_vertices.push_back(vertex(a, a, vec2(0,0)));
		sphere_vertices.push_back(vertex(b, b, vec2(0,1)));
		sphere_vertices.push_back(vertex(c, c, vec2(1,1)));
	}

	static void dividTriangle(vec3 a, vec3 b, vec3 c, int itertions)
	{
		if (itertions > 0)
		{
			vec3 v1 = normalize(a + b);
			vec3 v2 = normalize(a + c);
			vec3 v3 = normalize(b + c);

			dividTriangle(a, v1, v2, itertions - 1);
			dividTriangle(v1, b, v3, itertions - 1);
			dividTriangle(v1, v3, v2, itertions - 1);
			dividTriangle(v2, v3, c, itertions - 1);
		}
		else
		{
			Triangle(a, b, c);
		}
	}


public:

	static void CreateSphere(int iterations)
	{
		sphere_vertices.clear();
		dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[1], Sphere_Core_vertices[2], iterations);
		dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[3], Sphere_Core_vertices[1], iterations);
		dividTriangle(Sphere_Core_vertices[0], Sphere_Core_vertices[2], Sphere_Core_vertices[3], iterations);
		dividTriangle(Sphere_Core_vertices[3], Sphere_Core_vertices[2], Sphere_Core_vertices[1], iterations);

		glBufferData(GL_ARRAY_BUFFER, sphere_vertices.size() * sizeof(vertex), sphere_vertices.data(), GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (char*)(2 * sizeof(vec3)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(vertex), (char*)(sizeof(vec3)));
		glEnableVertexAttribArray(2);
	}


};

