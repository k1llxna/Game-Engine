#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <vector>
#include <optional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoords;
	Vertex(glm::vec3 pos_, glm::vec2 textureCoords_) : position(pos_), texCoords(textureCoords_) {}
};

class Particle {
public:
	Particle(GLuint shaderProgram_); // leave out texture id if no image assosiaction
	~Particle();
	void Render(class Camera* camera_);

	glm::vec3 GetPos() {
		return pos;
	}

	void SetPos(glm::vec3 pos_) {
		pos_ = pos;
	}

	glm::vec3 GetVel() {
		return vel;
	}

	void SetVel(glm::vec3 vel_) {
		vel_ = vel;
	}

	glm::vec3 GetCol() {
		return pos;
	}

	void SetCol(glm::vec3 col_) {
		col_ = col;
	}

	float GetLifetime() {
		return lifeTime;
	}

	void SetLifetime(float lifeTime_) {
		lifeTime_ = lifeTime;
	}

	void Update(const float deltaTime_);

private:
	void GenerateBuffers();
	friend class Emmiter;

	float lifeTime, size, angle;

	glm::vec3 pos, vel, col;
	std::vector<Vertex> vertexList;

	GLuint textureID;
	GLuint VAO, VBO; // optional!!
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc, textureLoc, colourLoc;
	GLuint viewPosition;
	GLuint sizeLoc; // !
};
#endif