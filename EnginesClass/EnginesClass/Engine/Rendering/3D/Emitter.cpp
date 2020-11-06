#include "Emitter.h"

Emitter::Emitter(int particles_, std::string shaderProgram_) : particleCount(particles_) { // no texture
	ShaderHandler::GetInstance()->CreateProgram(parVertexName, parShaderProgramName, parFragName);
	TextureHandler::GetInstance()->CreateTexture("", ""); // change
	particleShader = ShaderHandler::GetInstance()->GetShader("ParticleShader");
	textureID = TextureHandler::GetInstance()->GetTexture("ParticleTexture"); // ?
	if (textureID == 0 || particleShader == 0) {
		Debug::Error("failed to load particles", "Emitter.cpp", __LINE__);
	}
	else {
		particleList.reserve(particleCount);
		for (int i = 0; i < particleCount; i++) {
			Particle* newParticle = new Particle(particleShader, textureID);
			float x = rand() % 10 + 1;
			float y = rand() % 10 + 1;
			float z = rand() % 10 + 1;
			glm::vec3 rng(x, y, z);
			newParticle->SetVel(rng);
			newParticle->SetPos(glm::vec3(0));
			newParticle->SetLifetime(1.0f);
			particleList.push_back(newParticle);
		}
	}
}

Emitter::~Emitter() {

}

void Emitter::Update(Camera* cam_,const float deltaTime_) {
	for (auto i : particleList)
	{
		float newLifeTime = i->GetLifetime();
		newLifeTime - deltaTime_;
		if (newLifeTime <= 0) { // kill or reset
			ParticleLife(i);
		}
		else { // lifetime update
			i->SetLifetime(newLifeTime);
			glm::vec3 newVel = i->GetVel();
			glm::vec3 newPos = i->GetPos();
			newPos += newVel * deltaTime_;
			i->SetPos(newPos);
			i->Render(cam_);
		}
	}
}

void Emitter::ParticleLife(Particle* particle_) { // staggered values
	float x = rand() % 10 + 1;
	float y = rand() % 10 + 1;
	float z = rand() % 10 + 1;
	glm::vec3 rng(x, y, z);

	particle_->SetVel(rng);
	particle_->SetPos(glm::vec3(0));
	particle_->SetLifetime(1.0f);
}