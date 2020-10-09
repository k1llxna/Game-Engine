#include "EventListener.h"
#include "../Core/CoreEngine.h"

EventListener::~EventListener(){}

void EventListener::Update()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {	
				CoreEngine::GetInstance()->Exit();
		}
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_KEYDOWN:
			switch (sdlEvent.key.keysym.sym == SDLK_w) {
				 //Camera::ChangePos(Camera::GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f));
				CoreEngine::GetInstance()->GetCamera()->ChangePos(CoreEngine::GetInstance()->GetCamera()->GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f));
			
			}
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
		default:
			break;
		}
	}
}