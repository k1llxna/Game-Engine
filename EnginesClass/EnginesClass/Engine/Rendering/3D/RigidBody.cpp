#include "RigidBody.h"
#include "../../Core/Debug.h"


RigidBody::RigidBody() {}
RigidBody::~RigidBody() {}


void RigidBody::OnCreate(GameObject* go_) {
	Debug::Info("Created component", "ComponentSystem.cpp", __LINE__);
	go = go_;
}

void RigidBody::Update(float deltaTime_) {
	Debug::Info("Updating component", "ComponentSystem.cpp", __LINE__);
}