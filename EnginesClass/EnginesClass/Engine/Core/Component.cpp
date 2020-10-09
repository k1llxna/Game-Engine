#include "Component.h"

Component::Component() {
	go = nullptr;
}

Component::~Component() {
	go = nullptr;
	delete go;
}

//template<typename T>
void Component::OnCreate(class GameObject* go_) {
	go = go_;
}

void Component::Update(float deltaTime_) {
	// ?
}
