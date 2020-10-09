#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0) {}

Timer::~Timer() {}

void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks() {
	// Set prev to current THEN reset current
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const {
	return static_cast<float>((currentTicks - prevTicks) / 1000.0f);
	// static_cast = works or doesnt (not safety net)
	// dynamic_cast = returns nullptr if doesnt work
	// C cast forces (float)variable
}

unsigned int Timer::GetSleepTime(const unsigned int fps_) {
	// if it needs sleep/delay
	unsigned int milliPerFrame = 1000 / fps_;
	if (milliPerFrame == 0) {
		return 0;
		// no need to sleep/delay
	}

	unsigned int sleepTime = milliPerFrame - SDL_GetTicks();
	if (sleepTime > milliPerFrame) {
		return milliPerFrame;
	}
	return sleepTime;
}

float Timer::GetCurrentTicks() const {
	return static_cast<float>(currentTicks);
}