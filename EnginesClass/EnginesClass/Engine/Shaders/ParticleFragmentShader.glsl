#version 450 core

uniform vec3 Colour;

out vec4 fColour;

void main() {
	fColour = vec4(Colour, 1.0f);
}