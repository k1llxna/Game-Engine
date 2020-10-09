#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H
#include <SDL_opengl.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>

struct Vertex {
	glm::vec2 position;
	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	GLuint textureID;
};

class SpriteSurface {
public:
	SpriteSurface(std::string name_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_);
	~SpriteSurface();

	// get vertex points (triangles)
	void Draw();
	float GetWidth() { return width; }
	float GetHeight() { return height; }

private:
	GLuint VAO, VBO;
	glm::vec2 scale;
	std::string name;
	float angle, width, height;
};

#endif // !SPRITESURFACE_H