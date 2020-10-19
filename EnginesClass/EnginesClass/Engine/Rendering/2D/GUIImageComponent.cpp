#include "GUIImageComponent.h"

GUIImageComponent::GUIImageComponent() {
	sprite = NULL;
}

GUIImageComponent::~GUIImageComponent() {
	delete sprite;
	sprite = nullptr;
}

bool GUIImageComponent::OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 guiScale_ , float angle_, glm::vec4 tint_ ) {
	sprite = new SpriteSurface(imageName_, guiScale_, angle_, tint_);
	offset = offset_;
	return true;
}

void GUIImageComponent::Draw(Camera* cam_, glm::vec2 pos_) {
	if (sprite) {
		sprite->Draw(cam_, pos_);
	}// else error
}

void GUIImageComponent::FindContainingPoint() {
	if (sprite != nullptr) {}
}