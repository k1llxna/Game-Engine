#include "GameScene.h"
#include "../../Engine/Rendering/2D/GUIImageComponent.h"
#include "../../Engine/Audio/AudioHandler.h"



GameScene::GameScene() : Scene() {}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate() {
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	//Camera
	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 2.0f, 7.0f)); // set pos (account near plane)
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.8f));
	
	// Audio
	AudioHandler::GetInstance()->Init(CoreEngine::GetInstance()->GetCamera()->GetPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),glm::vec3(0.0f, 1.0f, 0.0f));

	// Emitter
	emitter = new Emitter(100);

	CollisionHandler::GetInstance()->OnCreate(100.0f); // world size

	Model* model1 = new Model("./Resources/Models/Apple.obj","./Resources/Materials/Apple.mtl" , ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(model1);

	Model* dice = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	SceneGraph::GetInstance()->AddModel(dice);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(dice));
	dice->SetPosition(glm::vec3(-5.0f, -2.0f, 0.0f));

	GameObject* apple = new GameObject(model1, glm::vec3(3.0f, -2.0f, 0.0f)); // alternative loading
	apple->SetScale(glm::vec3(1.0f));
	SceneGraph::GetInstance()->AddGameObject(apple, "Apple");
	//apple->AddComponent<Component>();
	apple->AddComponent<AudioSource>("MEHOYMINOYME.mp3", false, false, true);

	// gui
	GuiObject* guiObj = new GuiObject(glm::vec2(CoreEngine::GetInstance()->GetWindowSize().x / 2.0f, CoreEngine::GetInstance()->GetWindowSize().y / 2.0f));
	
	guiObj->AddComponent<GUIImageComponent>();
	guiObj->GetComponent<GUIImageComponent>()->OnCreate("db"); // name of png
	SceneGraph::GetInstance()->AddGuiObject(guiObj, "GuiShader");
	// , glm::vec2(1.0f,1.0f), glm::vec2(1.0f,1.0f), 0.0f, glm::vec4(1.0f,1.0f,1.0f,1.0f)
	
	return true;
}

void GameScene::Update(const float deltaTime_) {
	// std::cout << deltaTime_ << std::endl;
	SceneGraph::GetInstance()->Update(deltaTime_);
	
	emitter->Update(deltaTime_);
}

void GameScene::Render() {
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	emitter->Render(CoreEngine::GetInstance()->GetCamera());
}

void GameScene::Draw() {
//	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera());
}

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