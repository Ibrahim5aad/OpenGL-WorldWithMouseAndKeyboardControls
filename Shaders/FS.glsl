#version 330


uniform sampler2D colormap;

in vec2 frag_uv;
in vec3 v;
in vec3 n;
in vec3 l;
in vec3 h;

float ka = 0.5;
float kd = 0.8;
float ks = 5;
float sh = 50;

vec4 light_color = vec4(1,0.5,1,1);

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 lightIntencity = ka*light_color+
						  kd*max(dot(l,n),0)*light_color+
						  ks*max(pow(dot(h,n),sh),0)*vec4(1,1,1,1);

	gl_FragColor =  lightIntencity * texture(colormap,frag_uv);
}