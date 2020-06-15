#version 330

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec4 vertex_normal;

uniform mat4 modMat;
uniform mat4 viewMat;
uniform mat4 projMat;


out vec3 frag_position;
out vec3 frag_normal;

void main()
{
	gl_Position = projMat * viewMat * modMat * vertex_position;
	frag_position = (modMat * vertex_position).xyz;
	frag_normal = (transpose( inverse(modMat)) * vertex_normal).xyz;

}