#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp> // access to scale, translate, rotate etc
#include <string>
#include "LoadOBJModel.h"

class Model // Collections of meshes
{
public:
	Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_); // predeclared values r done at the end of parameter
	
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_); // create model object, then create meshes independantly
	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);

	glm::mat4 GetTransform(int index_) const;
	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);

	glm::vec3 GetPosition();
	float GetCollisionRadius();

private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;
	BoundingBox box;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	glm::vec3 position, rotation, scale;
	float angle, collisionRadius;
	void LoadModel();
};
#endif