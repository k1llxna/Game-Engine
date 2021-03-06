#include "Model.h"

Model::Model(const std::string& objFilePath_, const std::string& mtlFilePath_, GLuint shaderProgram_) : subMeshes(std::vector<Mesh*>()), shaderProgram(0), modelInstances(std::vector<glm::mat4>()) {
	subMeshes.reserve(10);
	shaderProgram = shaderProgram_;
	modelInstances.reserve(5);
	obj = new LoadOBJModel();
	obj->LoadModel(objFilePath_, mtlFilePath_);
	this->LoadModel();
}

Model::~Model()
{
	if (subMeshes.size() > 0) {
		for (auto m : subMeshes) { // auto is dataType (Mesh*) | temp name | name of collection
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
	}
	if (modelInstances.size() > 0) {
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera_) {
	glUseProgram(shaderProgram);
	for (auto m : subMeshes) {
		m->Render(camera_, modelInstances);
	}
}

void Model::AddMesh(Mesh* mesh_) {
	subMeshes.push_back(mesh_);
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstances.push_back(GetTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstances[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(int index_) const {
	return modelInstances[index_];
}

BoundingBox Model::GetBoundingBox()
{
	return box;
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

void Model::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void Model::SetAngle(float angle_)
{
	angle = angle_;
}

void Model::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
}

void Model::SetScale(glm::vec3 scale_)
{
	scale = scale_;
}

glm::vec3 Model::GetPosition()
{
	return position;
}

float Model::GetCollisionRadius()
{
	return collisionRadius;
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const {
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < obj->GetSubMeshes().size(); i++) {
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}

	box = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;
}
