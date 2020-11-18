#include "Emitter.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/ShaderHandler.h"
#include "Particle.h"

Emitter::Emitter(int particles_)  { // no texture
	
	particleShader = ShaderHandler::GetInstance()->GetShader("particleShader");
	
	if (particleShader == 0) {
		Debug::Error("failed to load particles", "Emitter.cpp", __LINE__);
	}

	else {
		//particleList.reserve(particleCount);
		for (int i = 0; i < particles_; i++) {
			Particle* newParticle = new Particle(particleShader);
			//scotts lib OPTIONAL
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

Emitter::~Emitter() {}

void Emitter::Update(const float deltaTime_) {
	for (auto i : particleList) {
		float newLifeTime = i->GetLifetime();
		newLifeTime -= deltaTime_; //-= decrement
		if (newLifeTime <= 0) { // kill or reset
			ParticleLife(i);
		}
		else { // lifetime update
			i->SetLifetime(newLifeTime);
			glm::vec3 newVel = i->GetVel();
			glm::vec3 newPos = i->GetPos();
			newPos += newVel * deltaTime_;
			i->SetPos(newPos);
		}
	}
}

void Emitter::Render(Camera* cam_) {
	glEnable(GL_BLEND);
	glUseProgram(particleShader);
	for (auto i : particleList) {
		i->Render(cam_);
	}
	glDisable(GL_BLEND);
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