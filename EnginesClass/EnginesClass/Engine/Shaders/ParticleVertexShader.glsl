#version 450 core 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float size;

void main() {
	gl_Position = proj * view * model * vec4(0.0f,0.0f,0.0f, 1.0f);
	float distToCam = length((view * model * vec4(0.0f,0.0f,0.0f, 1.0f)).xyz);
	float Attenuation = inversesqrt(0.1f * distToCam);
	gl_PointSize = Attenuation * size;
}