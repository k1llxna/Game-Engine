#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "GUIComponent.h"
#include "../../Core/Debug.h"

class GuiObject { // any 2d object, base class
public:
	GuiObject(glm::vec2 position_);
	~GuiObject();

	void Draw(Camera* cam_);
	void SetTag(std::string tag_);

	template<typename A>
	void AddComponent() {
		A* t = new A();
		if (dynamic_cast<GUIComponent*>(t)) { // new obj is child of component base class
			if (GetComponent<A>()) { // check if component type already exists
				Debug::Info("Failed to add component, component already exists. Deleting component", "GuiObject.cpp", __LINE__);
				delete t;
				t = nullptr;
				return;
			}
			else if (GetComponent<A>() == nullptr) { // no other type, greenlight
				guiContainer.push_back(t);
				Debug::Info("Added component", "GuiObject.cpp", __LINE__);
			}
		}
		else { // not child of comp class
			Debug::Info("Object is not a child of component. Deleting component", "GuiObject.cpp", __LINE__);
			delete t;
			t = nullptr;
			return;
		}
	}

	template<typename g>
	g* GetComponent() { // 1 component per type assumption
		for (auto m : guiContainer) {
			if (dynamic_cast<g*>(m)) {
				return  dynamic_cast<g*>(m); 
			}
			return nullptr;
		}
	}

	template<typename r>
	void removecomponent() {
		for (int i = 0; i < guiContainer.size(); i++) {
			if (r = dynamic_cast<r*>(guiContainer[i])) {
				delete guiContainer[i];
				guiContainer[i] = nullptr;
				guiContainer.erase(guiContainer.begin() + i);
			}
		}
	}

private:
	glm::vec2 position;
	std::string tag;
	std::vector<GUIComponent*> guiContainer;
};
#endif
// image animation textcomponents<spriteObject(opengl)>
// hud, menu
// gui - orhtographic vs gameobject - perspective