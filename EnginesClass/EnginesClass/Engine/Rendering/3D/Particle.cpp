#include "Particle.h"
#include "../../Camera/Camera.h"

Particle::Particle(GLuint shaderProgram_) { // ID for images
	shaderProgram = shaderProgram_; // save BEFORE gen buffers
	size = 10;
	vel = glm::vec3(2.0f);
	col = glm::vec3(0.0f, 1.0f, 0.0f); // green
	lifeTime = 3.0f;
	GenerateBuffers();
}

Particle::~Particle() {
	glDeleteVertexArrays(1, &VAO); // &address from non pointers
	glDeleteBuffers(1, &VBO);

	if (vertexList.size() > 0) {
		vertexList.clear();
	}
}

void Particle::Render(Camera* camera_) { // view matrice, model, coolour, texture

	glEnable(GL_PROGRAM_POINT_SIZE);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));

	glUniform3fv(colourLoc, 1, glm::value_ptr(col)); 

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));

	glUniform1f(sizeLoc, size);
	glBindVertexArray(VAO);

	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0); 
	glDisable(GL_PROGRAM_POINT_SIZE);
}

/*
//// set uniforms
	//glUniform1i(textureLoc, 0); // in theory more than 1 text on same object (texturedUnit)
	//glActiveTexture(GL_TEXTURE0); // swith texture

	//glBindTexture(GL_TEXTURE_2D, textureID);
//model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
//glm::vec4 distance = camera_->GetView() * model * glm::vec4(pos, 1.0f);
//glm::vec4 attenuation = distance * glm::inversesqrt(0.1f); // can do in v shader
//model = glm::scale(model, glm::vec3(size * attenuation));

// location, quantity, transpose, gl ptr(transform)
//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_)); // make sure its mat4

//glBlendFunc(GL_SRC_ALPHA, GL_ONE); // addivtive blending
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // real transparency
*/

void Particle::GenerateBuffers() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // puts stuff in gpu

	glBindVertexArray(0);

	// position
	/*glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);*/

	glBindVertexArray(0); // closes gpu door

	// get unifrom loc *OPTIONAL FOR PARTICLE RENDERING* 
	modelLoc = glGetUniformLocation(shaderProgram, "model"); // SPELLING!
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
	sizeLoc = glGetUniformLocation(shaderProgram, "size"); 
}

//// texCoords
//glEnableVertexAttribArray(3);
//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));


void Particle::Update(const float deltaTime_) {
	lifeTime -= deltaTime_;
	pos = deltaTime_ * vel;
}