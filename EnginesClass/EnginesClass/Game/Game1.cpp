#include "Game1.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr) {}

Game1::~Game1(){
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) { //
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::FatalError("Engine's scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_) { // Update THEN Render
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) { // check to change scene
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render() {
	currentScene->Render(); ///
}

void Game1::BuildScene() { // gamescene != coreengine scene
	// switching scenes
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) {
	case 1: // Set up Enums
		currentScene = new GameScene();
		break;
	default: // case 0:
		currentScene = new StartScene();
		break;
	}
	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) { // if == false
		CoreEngine::GetInstance()->Exit();
	}
}

void Game1::Draw() {
	currentScene->Draw();
}

void Game1::Update() {}