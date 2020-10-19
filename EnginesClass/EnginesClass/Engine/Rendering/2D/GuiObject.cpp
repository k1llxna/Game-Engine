#include "GuiObject.h"
#include "../../Camera/Camera.h"

GuiObject::GuiObject(glm::vec2 position_) {
	position = position_;
}

GuiObject::~GuiObject() {}

void GuiObject::Draw(Camera* cam_) {
	for (auto g : guiContainer) {
		g->Draw(cam_, position);
	}
}

void GuiObject::SetTag(std::string tag_) {
	tag = tag_;
}