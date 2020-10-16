#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>

#include "3D/GameObject.h"
#include "../Math/CollisionHandler.h"
#include "../Rendering/2D/GuiObject.h"
#include "../Core/CoreEngine.h"

class SceneGraph {
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();

	void OnDestroy();
	void AddModel(Model* model_);
	void AddGameObject(GameObject* gameObject_, std::string tag_ = "");
	void AddGuiObject(GuiObject* guiObject_, std::string tag_ = "");

	GameObject* GetGameObject(std::string tag_);
	GuiObject* GetGuiObject(std::string tag_);

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	void Draw(Camera* camera_);

private:
	SceneGraph();
	~SceneGraph();

	static std::unique_ptr<SceneGraph> sceneGraphInstance;
	friend std::default_delete<SceneGraph>;

	static std::map<GLuint, std::vector<Model*>> sceneModels;
	static std::map<std::string, GameObject*> sceneGameObjects;
	static std::map<std::string, GuiObject*> guiObjects;
};
#endif