#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_) : VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0) { // ID for images
	shaderProgram = shaderProgram_; // save BEFORE gen buffers
	GenerateBuffers();
}

Particle::~Particle() {
	//glDeleteVertexArrays(1, &VAO); // &address from non pointers
	//glDeleteBuffers(1, &VBO);

	//if (subMesh.vertexList.size() > 0) {
	//	subMesh.vertexList.clear();
	//}

	//if (subMesh.meshIndices.size() > 0) {
	//	subMesh.meshIndices.clear();
	//}
}

void Particle::Render(Camera* camera_) { // view matrice, model, coolour, texture

	glEnable(GL_PROGRAM_POINT_SIZE);

	// set uniforms
	glUniform1i(textureLoc, 0); // in theory more than 1 text on same object (texturedUnit)
	glActiveTexture(GL_TEXTURE0); // swith texture

	glBindTexture(GL_TEXTURE_2D, textureID);

	// create own matrix
	glm::mat4 model;
	glm::vec4 distance = camera_->GetView() * model * glm::vec4(pos, 1.0f);
	glm::vec4 attenuation = distance * glm::inversesqrt(0.1f);
	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size * attenuation));

	// location, quantity, transpose, gl ptr(transform)
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_)); // make sure its mat4
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // addivtive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // real transparency

	glBindVertexArray(VAO);

	glDrawArrays(GL_POINTS, 0, 1);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(0); // shut down
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Particle::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); // puts stuff in gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex), &vertexList[0], GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// texCoords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0); // closes gpu door
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// get unifrom loc *OPTIONAL FOR PARTICLE RENDERING* 
	modelLoc = glGetUniformLocation(shaderProgram, "model"); // SPELLING!
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
}