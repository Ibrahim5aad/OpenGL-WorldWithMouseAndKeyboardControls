in vec3 frag_position;
in vec3 frag_normal;

uniform samplerCube cubemap;  
uniform vec3 camPos;

void main()
{             
	vec3 r = reflect(normalize(frag_position - camPos), normalize(frag_normal));
    gl_FragColor = vec4(texture(cubemap, r).rgb,1.0);
}