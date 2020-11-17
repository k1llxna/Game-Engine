#ifndef EMITTER_H
#define EMITTER_H

#include <string>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <vector>

#include "../../Core/Component.h"

class Particle;

class Emitter { // public Component
public:
	Emitter(int particles_, std::string shaderProgram_);
	~Emitter();

	void Update(const float deltaTime_); // combined w render, for component inheritence
	void Render(class Camera* cam_);
	void ParticleLife(Particle* particle_);

	const std::string parVertexName, parFragName;

private:
	std::vector<Particle*> particleList;
	int particleCount;
	std::string parNameTexture;
	const std::string parShaderProgramName;
	GLuint particleShader, textureID;
};
#endif