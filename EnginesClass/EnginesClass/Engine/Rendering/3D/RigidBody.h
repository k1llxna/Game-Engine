#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../Core/Component.h"

class RigidBody : Component {
public:
	RigidBody();
	virtual ~RigidBody();

	virtual void OnCreate(GameObject* go_) override;
	virtual void Update(float deltaTime_) override;
};
#endif // !RIGIDBODY_H