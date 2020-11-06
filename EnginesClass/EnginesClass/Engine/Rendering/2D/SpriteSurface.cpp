#include "SpriteSurface.h"
#include "../../../Engine/Graphics/ShaderHandler.h"

SpriteSurface::SpriteSurface(std::string name_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0), colourLoc(0)  {
	vertexList.push_back(Vertex2D(glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f)));
	vertexList.push_back(Vertex2D(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 1.0f)));

	imageScale = glm::vec2(scale_);
	angle = angle_;
	tintColour = tintColour_;
	if (name_ != "") {
		imageLoader = name_;
	}
	
	if (TextureHandler::GetInstance()->GetTexture(imageLoader) == 0) {
		TextureHandler::GetInstance()->CreateTexture(imageLoader, "./Resources/Textures/" + imageLoader + ".png"); // create texture, load png image
	}

	textureID = TextureHandler::GetInstance()->GetTexture(imageLoader);
	width = TextureHandler::GetInstance()->GetTextureData(imageLoader)->width;
	height = TextureHandler::GetInstance()->GetTextureData(imageLoader)->height;

	GenerateBuffers();
}

SpriteSurface::~SpriteSurface() {
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO); // verttext buffer obj
}

void SpriteSurface::Draw(Camera* cam_, glm::vec2 pos_) {
	
	glUniform1d(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, textureID);

	// create own matrix
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 0));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(width * imageScale.x, height * imageScale.y, 1.0f));

	// sending colour	R G B A
	glUniform4fv(colourLoc, 1, glm::value_ptr(glm::vec4(tintColour.r, tintColour.g, tintColour.b, tintColour.a)));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam_->GetOrthographic()));

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

float SpriteSurface::GetWidth() { 
	return width; 
}

float SpriteSurface::GetHeight() { 
	return height; 
}

void SpriteSurface::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); // puts stuff in gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	// offset (index), amount of data, data type, normalized?, space between conseq v attributes, offset. EX: | P | N | T | C |
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	// texCoords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, textCoords));

	glBindVertexArray(0); // closes gpu door
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	spriteShaderProgram = ShaderHandler::GetInstance()->GetShader("spriteColourShader");

	// get unifrom loc...SPELLING!
	colourLoc = glGetUniformLocation(spriteShaderProgram, "tintColour");
	modelLoc = glGetUniformLocation(spriteShaderProgram, "model"); 
	viewLoc = glGetUniformLocation(spriteShaderProgram, "view");
	projLoc = glGetUniformLocation(spriteShaderProgram, "proj");
	textureLoc = glGetUniformLocation(spriteShaderProgram, "inputTexture");
}
