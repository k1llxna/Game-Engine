#version 450 core 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float size;

void main() {
	gl_Position = proj * view * model * vec4(0.0f,0.0f,0.0f, 1.0f);
	vec4 translate = view * model * vec4(0.0f,0.0f,0.0f, 1.0f);
	float distToCam = length(translate.xyz);
	float attenuation = inversesqrt(0.1f * distToCam);
	gl_PointSize = attenuation * size;
}