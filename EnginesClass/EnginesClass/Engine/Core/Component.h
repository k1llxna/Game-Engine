#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	inline Component();
	virtual inline ~Component();

	virtual void OnCreate(class GameObject* go_) = 0; // = 0
	virtual void Update(float deltaTime_) = 0;

protected:
	GameObject* go;
};
#endif // !COMPONENT_H