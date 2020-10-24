#ifndef COMPONENT_H
#define COMPONENT_H

//#include "../Rendering/3D/GameObject.h"

class Component {
public:
	virtual bool OnCreate(class GameObject* go_) = 0; // = 0
	virtual void Update(float deltaTime_) = 0;

protected:
	 GameObject* go;	
};
#endif // !COMPONENT_H
// oncreate -> go = go_ go = nullptr; delete go;