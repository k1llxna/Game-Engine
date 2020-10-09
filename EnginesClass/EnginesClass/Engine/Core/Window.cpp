#include "Window.h"

Window::Window() : width(0), height(0), window(nullptr) {}


Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::Error("Failed to initialized SDL", "Window.cpp", __LINE__); // std::cout << "Failed to initialized SDL" << std::endl;
		return false;
	}
	width = width_;
	height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//! can be used since window is a pointer
	if (!window) { // OR window == nullptr

		Debug::Info("Creating Window", "Window.cpp", __LINE__); // std::cout << "Failed to create window" << std::endl; // to debug lines
		
		return false;
	}

	//Door to GPU
	context = SDL_GL_CreateContext(window);

	SetPostAttributes();

	GLenum error = glewInit(); // access API

	if (error != GLEW_OK) {
		Debug::Info("Failed to initialize GLEW", "Window.cpp", __LINE__); // std::cout << "Failed to initialize GLEW" << std::endl;		
		return false;
	}

	//enable depth testing takes Z into account
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);
	// if resize -> reset viewport

	//desplay specs (vendor)
	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Window::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window); // DELETE BEFORE SETTING TO NULLPTR
	window = nullptr;
}

int Window::GetWidth() {
	return width;
}

int Window::GetHeight() {
	return height;
}

SDL_Window* Window::GetWindow() const {
	return window;
}

void Window::SetPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1); // vertically in sync with retrace

	// before init glew
	glewExperimental = GL_TRUE;
}

void Window::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32); // Set bit size for depth buffer
}