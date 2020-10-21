#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include <glew.h>
#include <glm/glm.hpp>
#include <string>
#include "../../Camera/Camera.h"
#include "GUIComponent.h"

class GUIImageComponent : public GUIComponent {
public:
	GUIImageComponent();
	virtual ~GUIImageComponent();

	virtual void Draw(Camera* cam_, glm::vec2 pos_) override;
	virtual void FindContainingPoint();

	virtual bool OnCreate(std::string imageName_, glm::vec2 offset_ = glm::vec2(0.0f, 0.0f), glm::vec2 guiScale_ = glm::vec2(1.0f, 1.0f), float angle_ = 0.0f, glm::vec4 tint_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) override;

private:
	class SpriteSurface* sprite;
	glm::vec2 offset;
};
#endif 