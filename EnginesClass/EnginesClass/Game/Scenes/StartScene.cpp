#include "StartScene.h"

StartScene::StartScene() : Scene()
{ // Calling parents constructor
}

StartScene::~StartScene(){}

bool StartScene::OnCreate() {
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetCurrentScene(1); // trigger a scene switch
	return true;
}

void StartScene::Update(const float deltaTime_) {}
void StartScene::Render() {}
void StartScene::Draw() {}