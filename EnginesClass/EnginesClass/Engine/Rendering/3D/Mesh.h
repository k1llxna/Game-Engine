#ifndef MESH_H
#define MESH_H

// unifrom = variable in shader, can be changed in c++ (get location(shader ID) call shader program)

// Non introleaved (vectors)
// vbo vao are stored here
#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera_, std::vector<glm::mat4> instances_);

private:
	void GenerateBuffers();
	SubMesh subMesh;

	GLuint VAO, VBO; // vertex

	GLuint shaderProgram;
	GLuint textureID;

	GLuint modelLoc, viewLoc, projLoc, textureLoc;
	GLuint viewPosition;

	GLuint lightPositionLoc, lightAmbientLoc, lightDiffuseLoc, lightColourLoc;
};
#endif