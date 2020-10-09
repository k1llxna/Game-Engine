#include "Camera.h"
#include "../Core/CoreEngine.h"
//#include "../EnginesClass/Engine/Core/CoreEngine.h" // avoids circular dependency

Camera::Camera() : position(glm::vec3()) {
	fieldOfView = 45.0f,
	forward = glm::vec3(0.0f, 0.0, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f); // roll
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y,
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVector();
}

Camera::~Camera(){
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
	//UpdateCameraVector();
}

void Camera::SetRotation(float yaw_, float pitch_) {
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const {
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const {
	return perspective; // resizable in future
}

glm::mat4 Camera::GetOrthographic() const {
	return orthographic;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

void Camera::UpdateCameraVector() {
	// CODES ALWAYS IN DEGREES OR radians

	//cross prod right hand (gang sign)
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// always normalized, keep magnitude to 1
	forward = glm::normalize(forward);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}


void Camera::OnDestroy() {
	lightSources.clear();
}

void Camera::AddLightSource(LightSource* lightSource_) {
	lightSources.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightSources() const
{
	return lightSources;
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

glm::vec3 Camera::GetForward() const
{
	return forward;
}

glm::vec3 Camera::GetUp() const
{
	return up;
}

glm::vec3 Camera::GetRight() const
{
	return right;
}

glm::vec3 Camera::GetWorldUp() const
{
	return worldUp;
}

float Camera::GetFOV() const
{
	return fieldOfView;
}

void Camera::ChangePos(glm::vec3 newPos_)
{
	position = newPos_;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;
	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 360.0f;
	}

	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVector();
}

/* plane intersection algorithom (FRUSTUM CULL)
dn = back to origin

project vector onto n
(p . n ) * n

e = p . n
d = plane loc to origin
c = e + d
p . n + d + r
*/