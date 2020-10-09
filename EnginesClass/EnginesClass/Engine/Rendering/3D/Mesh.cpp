#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) :   VAO(0), VBO(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0) {
	shaderProgram = shaderProgram_; // save BEFORE gen buffers
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO); // &address from non pointers
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_) {

	// set uniforms
	glUniform1i(textureLoc, 0); // in theory more than 1 text on same object (texturedUnit)
	glActiveTexture(GL_TEXTURE0); // swith texture
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	// location, quantity, transpose, gl ptr(transform)
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform_)); // make sure its mat4
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	
	glUniform1f(lightAmbientLoc, camera_->GetLightSources().at(0)->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSources().at(0)->GetDiffuse());
	glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera_->GetLightSources().at(0)->GetColor()));
	glUniform3fv(lightPositionLoc, 1, glm::value_ptr(camera_->GetLightSources().at(0)->GetPosition()));
	
	glUniform3fv(viewPosition, 1, glm::value_ptr(camera_->GetPosition()));

	// bind vao again
	glBindVertexArray(VAO);
	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		
		// shape, start, how many V's
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	//elements includes indecies | not always supported
	glBindVertexArray(0); // shuts 
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() { // call AFTER save vertexlist
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); // puts stuff in gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	// offset (index), amount of data, data type, normalized?, space between conseq v attributes, offset. EX: | P | N | T | C |
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// normal
	glEnableVertexAttribArray(1); // creating an array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// texCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	// colour
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0); // closes gpu door
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// get unifrom loc
	modelLoc = glGetUniformLocation(shaderProgram, "model"); // SPELLING!
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	// set light loc
	viewPosition = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColour");
}