#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(60), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

CoreEngine* CoreEngine::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine());
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::Error("Window failed to initialized", "CoreEngine.cpp", __LINE__); // std::cout << "Window failed to initialized" << std::endl;
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	// vertex THEN fragment
	// colourShader
	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");

	// shader
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	// GUI shader (for 2D objects)
	ShaderHandler::GetInstance()->CreateProgram("spriteColourShader", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");

	// emitter
	ShaderHandler::GetInstance()->CreateProgram("particleShader", "Engine/Shaders/ParticleVertexShader.glsl", "Engine/Shaders/ParticleFragmentShader.glsl");

	// create interface, make sure it has been set
	if (gameInterface) { // gameInterface != nullptr // because its a ptr
		if (!gameInterface->OnCreate()) {
			// DEBUG
			Debug::Error("Game failed to create", "CoreEngine.cpp", __LINE__);
		}
	}

	timer.Start();

	Debug::Info("Everything worked!", "CoreEngine.cpp", __LINE__); 
	return isRunning = true;
}

// Update Render
void CoreEngine::Run() {
	while (isRunning) {
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const {
	return isRunning;
}

void CoreEngine::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render() {
	// add background color
	glClearColor(1.0f, 0.0f, 1.0f, 0.5f);

	// clear buffer bits gets rid of artifacts (previous renders)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// RENDER GAME HERE
	if (gameInterface) {
		gameInterface->Render();
		gameInterface->Draw();
	}

	// Swap window after
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() { // delete calls destructor, setting nullptr removes all contents (for pointers)

	CollisionHandler::GetInstance()->OnDestroy();

	delete camera;
	camera = nullptr;
	delete gameInterface;
	gameInterface = nullptr;
	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
} // shader, texture handelrs = ondesetroy

void CoreEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene() {
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit() {
	isRunning = false;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_){}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_) {
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

glm::vec2 CoreEngine::GetWindowSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

Camera* CoreEngine::GetCamera() const {
	return camera;
}

void CoreEngine::SetCamera(Camera* camera_) {
	camera = camera_;
}
// diff camera children doesnt require much change