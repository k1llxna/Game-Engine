#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include <glew.h>
#include <glm/glm.hpp>
#include <string>
#include "../../Camera/Camera.h"

class GUIComponent { //  virtual parent class
public:
	inline GUIComponent() {			};
	virtual inline ~GUIComponent() {		};

	virtual void Draw(Camera* cam_, glm::vec2 pos_) = 0;
	virtual void FindContainingPoint() = 0;

	virtual bool OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 guiScale_, float angle_, glm::vec4 tint_) = 0;
};
#endif