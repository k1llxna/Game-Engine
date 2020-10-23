#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels =
std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects =
std::map<std::string, GameObject*>();

std::map<std::string, GuiObject*> SceneGraph::guiObjects =
std::map<std::string, GuiObject*>();

SceneGraph::SceneGraph(){}
SceneGraph::~SceneGraph(){
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}

	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0) {
		for (auto gameObject : sceneGameObjects) {
			delete gameObject.second;
			gameObject.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (guiObjects.size() > 0) {
		for (auto guiObject : guiObjects) {
			delete guiObject.second;
			guiObject.second = nullptr;
		}
		guiObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_)
{
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> temp = std::vector<Model*>();
		temp.reserve(10);
		temp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), temp));
	}
	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* gameObject_, std::string tag_)
{
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gameObject_;
	}

	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		gameObject_->SetTag(tag_);
		sceneGameObjects[tag_] = gameObject_;
	}

	else {
		Debug::Error("Trying to add GameObject with tag" + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		gameObject_->SetTag(newTag);
		sceneGameObjects[newTag] = gameObject_;
	}

	CollisionHandler::GetInstance()->AddObject(gameObject_);
}

void SceneGraph::AddGuiObject(GuiObject* guiObject_, std::string tag_)
{ // map
	if (tag_ == "") {
		std::string newTag = "GuiObject" + std::to_string(guiObjects.size() + 1);
		guiObject_->SetTag(newTag);
		guiObjects[newTag] = guiObject_;
	}

	else if (guiObjects.find(tag_) == guiObjects.end()) {
		guiObject_->SetTag(tag_);
		guiObjects[tag_] = guiObject_;
	}

	else {
		Debug::Error("Trying to add GuiObject with tag" + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GuiObject" + std::to_string(guiObjects.size() + 1);
		guiObject_->SetTag(newTag);
		guiObjects[newTag] = guiObject_;
	}
}

GuiObject* SceneGraph::GetGuiObject(std::string tag_) {
	if (guiObjects.find(tag_) != guiObjects.end()) {
		return guiObjects[tag_];
	}
	return nullptr;
}

GameObject* SceneGraph::GetGameObject(std::string tag_) {
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);

		for (auto m : entry.second) {
				m->Render(camera_);
		}
	}
}

void SceneGraph::Draw(Camera* camera_) {
	glUseProgram(ShaderHandler::GetInstance()->GetShader("spriteColourShader"));//
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto g : guiObjects) {
		g.second->Draw(camera_);
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}