#version 330

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec4 vertex_normal;
layout (location = 3) in mat4 modelMat;

uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 modMat;
uniform vec3 camPos;

vec3 light_position = vec3(5, 100, -5);
vec3 light_direction = light_position - (modelMat * modMat * vertex_position).xyz ;


out vec2 frag_uv;
out vec3 v;
out vec3 n;
out vec3 l;
out vec3 h;


void main()
{
	gl_Position = projMat * viewMat * modelMat * modMat * vertex_position;
	frag_uv = vertex_uv;


	l = normalize(light_direction);
	n = normalize(normalize(modelMat *  vec4(vertex_normal)).xyz);
	v = normalize(camPos - (modelMat *  vec4(vertex_position)).xyz);
	h = normalize(v+l);

}