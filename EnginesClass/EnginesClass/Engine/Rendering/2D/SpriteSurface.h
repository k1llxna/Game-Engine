#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "../../Graphics/TextureHandler.h"
#include "../../Camera/Camera.h"

struct Vertex2D {
	glm::vec2 position;
	glm::vec2 textCoords;
	Vertex2D(glm::vec2 position_, glm::vec2 textCoords_) { // constructor
		position = position_;
		textCoords = textCoords_;
	};
};

class SpriteSurface {
public:
	SpriteSurface(std::string name_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_);
	~SpriteSurface();

	// get vertex points (triangles)
	void Draw(Camera* cam_, glm::vec2 pos_);
	float GetWidth(), GetHeight(); // 2 lines

private:
	GLuint VAO, VBO, modelLoc, viewLoc, projLoc, textureLoc, colourLoc;	
	float angle, width, height;

	GLuint textureID = 0;
	GLuint spriteShaderProgram;
	std::string imageLoader;
	std::vector<Vertex2D> vertexList;

	glm::vec4 tintColour;
	glm::vec2 imageScale, position;

	void GenerateBuffers();
};

#endif // !SPRITESURFACE_H