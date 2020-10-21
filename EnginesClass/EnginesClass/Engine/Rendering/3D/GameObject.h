#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Core/Component.h"
#include "../../Core/Debug.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3()); // can pass nullptr for empty gameObj
	~GameObject();
	void Render(Camera* camera_);
	void Update(float deltaTime_);

	glm::vec3 GetPosition() const; 
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	bool GetHit() const;
	std::string GetTag() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	BoundingBox GetBoundingBox();

	template<typename A>
	void AddComponent() {
		A* t = new A();
		Debug::Info("Instance created", "GameObject.cpp", __LINE__);
		if (dynamic_cast<Component*>(t)) { // new obj is child of component base class
			if (GetComponent<A>()) { // check if component type already exists
				Debug::Info("Failed to add component, component already exists. Deleting component", "GameObject.cpp", __LINE__);
				delete t;
				t = nullptr;
				return;
			}
			else if (GetComponent<A>() == nullptr) { // no other type, greenlight
				objects.push_back(t);
				t->OnCreate(this);
				Debug::Info("Added component", "GameObject.cpp", __LINE__);
			}
		}
		else { // not child of comp class
			Debug::Info("Object is not a child of component. Deleting component", "GameObject.cpp", __LINE__);
			delete t;
			t = nullptr;
			return;
		}
	}

	template<typename G>
	G* GetComponent() { // 1 component per type assumption
		for (auto m : objects) {
			if (dynamic_cast<G*>(m)) {
				return  dynamic_cast<G*>(m); // return G?
			}
			return nullptr;
		}
	}

	template<typename R>
	void RemoveComponent() {
		for (int i = 0; i < objects.size(); i++) {
			if (R = dynamic_cast<R*>(objects[i])) {
				delete objects[i];
				objects[i] = nullptr;
				objects.erase(objects.begin() + i);  //erase from vecter ?
			}
		}
	}

private:
	Model * model;

	glm::vec3 position, rotation, scale;

	float angle;
	int modelInstance;

	BoundingBox box;
	std::string tag;

	bool hit;

	std::vector<Component*> objects;
};
#endif