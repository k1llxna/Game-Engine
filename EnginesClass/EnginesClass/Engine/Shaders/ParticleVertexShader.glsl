#version 450 core 
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 colour;
layout (location = 5) in float size;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Colour;
out vec4 Attenuation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(position, 1.0f);
	Normal =  normal;
	TexCoords = texCoords;
	Colour = colour;
	Attenuation = InvSqrt(0.1f *(view * model * vec4(position, 1.0f)));
	gl_PointSize = Attenuation * size;
}