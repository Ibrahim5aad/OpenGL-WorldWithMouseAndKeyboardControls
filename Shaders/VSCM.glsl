#version 330
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec4 vertex_color;

uniform mat4 mvp_mat;

out vec3 frag_uv0;


void main()
{
	gl_Position = mvp_mat*vec4(vertex_position,1);
	frag_uv0 = vertex_position;
}