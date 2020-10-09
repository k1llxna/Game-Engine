#include "GameScene.h"

GameScene::GameScene() : Scene() {}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate() {
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 2.0f, 7.0f)); // set pos (account near plane)
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.8f));
	
	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model1 = new Model("./Resources/Models/Apple.obj","./Resources/Materials/Apple.mtl" , ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	Model* model2 = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model2);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(model2));

	GameObject* apple = new GameObject(model1, glm::vec3(4.0f, -1.0f, 0.0f)); // alternative loading
	apple->SetScale(glm::vec3(0.3f));
	//apple->AddComponent<Component>();
	SceneGraph::GetInstance()->AddGameObject(apple, "Apple");

	return true;
}

void GameScene::Update(const float deltaTime_) {
	// std::cout << deltaTime_ << std::endl;
	SceneGraph::GetInstance()->Update(deltaTime_);
	//compSystem->Update(deltaTime_);
}

void GameScene::Render() {
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
}

void GameScene::Draw() {}

// old models
/*v.position = glm::vec3(-0.5f, 0.7f, 0.0f);
v.colour = glm::vec3(1.0f, 0.0f, 0.0f); ///
vertexList.push_back(v);

v.position = glm::vec3(0.5f, 0.7f, 0.0f);
v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(0.0f, 0.0f, 0.0f);
v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
vertexList.push_back(v);

model->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));
vertexList.clear();


v.position = glm::vec3(0.7f, 0.5f, 0.0f);
v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(0.7f, -0.5f, 0.0f);
v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(0.0f, 0.0f, 0.0f);
v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
vertexList.push_back(v);

model->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));
vertexList.clear();

v.position = glm::vec3(0.5f, -0.7f, 0.0f);
v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(-0.5f, -0.7f, 0.0f);
v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(0.0f, 0.0f, 0.0f);
v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
vertexList.push_back(v);

model->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("colourShader")));
vertexList.clear();


v.position = glm::vec3(-0.7f, -0.5f, 0.0f);
v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(-0.7f, 0.5f, 0.0f);
v.colour = glm::vec3(0.0f, 1.0f, 0.0f);
vertexList.push_back(v);

v.position = glm::vec3(0.0f, 0.0f, 0.0f);
v.colour = glm::vec3(0.0f, 0.0f, 1.0f);
vertexList.push_back(v);*/