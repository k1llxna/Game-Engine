#include "Frustum.h"
#include "../Camera/Camera.h"

void Frustum::CreateFrustum() // world space
{
	frustumPlanes.clear();

	float nearFrustumHeight = glm::tan(camera->GetFOV() / 2) * nearClippingDistance;
	float nearFrustumWidth = nearFrustumHeight * screenRatio;

	float farFrustumHeight = glm::tan(camera->GetFOV() / 2) * farClippingDistance;
	float farFrustumWidth = farFrustumHeight * screenRatio;

	glm::vec3 farClippingCenter = camera->GetPosition() + camera->GetForward() * farClippingDistance;
	glm::vec3 nearClippingCenter = camera->GetPosition() + camera->GetForward() * nearClippingDistance;
	glm::vec3 normalPlane;

	// camera right and up
	camera->UpdateCameraVector();

	// near clip
	frustumPlanes.push_back(Plane(camera->GetForward(), glm::dot(-camera->GetForward(), nearClippingCenter)));

	// far
	frustumPlanes.push_back(Plane(camera->GetForward(), glm::dot(-camera->GetForward(), farClippingCenter)));

	// right
	normalPlane = -glm::normalize(glm::cross(camera->GetUp(), (farClippingCenter + camera->GetRight() * farFrustumWidth) - camera->GetPosition()));
	frustumPlanes.push_back(Plane(normalPlane, glm::dot(-normalPlane, camera->GetPosition())));

	// left
	normalPlane = glm::normalize(glm::cross(camera->GetUp(), (farClippingCenter - camera->GetRight() * farFrustumWidth) - camera->GetPosition()));
	frustumPlanes.push_back(Plane(normalPlane, glm::dot(-normalPlane, camera->GetPosition())));

	// top
	normalPlane = -glm::normalize(glm::cross(camera->GetRight(), (farClippingCenter + camera->GetUp() * farFrustumHeight) - camera->GetPosition()));
	frustumPlanes.push_back(Plane(normalPlane, glm::dot(-normalPlane, camera->GetPosition())));

	// bottom
	normalPlane = glm::normalize(glm::cross(camera->GetRight(), (farClippingCenter - camera->GetUp() * farFrustumHeight) - camera->GetPosition()));
	frustumPlanes.push_back(Plane(normalPlane, glm::dot(-normalPlane, camera->GetPosition())));

	frustum = true;
}

bool Frustum::isSphereInView(glm::vec3 center_, float radius_)
{
	if (!frustum) {
		CreateFrustum();
	}

	// check if point is in frustum
	if (frustumPlanes[0].GetDistance(center_) < -radius_) {
		return false;
	}

	if (frustumPlanes[1].GetDistance(center_) < -radius_) {
		return false;
	}

	if (frustumPlanes[2].GetDistance(center_) < -radius_) {
		return false;
	}

	if (frustumPlanes[3].GetDistance(center_) < -radius_) {
		return false;
	}

	if (frustumPlanes[4].GetDistance(center_) < -radius_) {
		return false;
	}

	if (frustumPlanes[5].GetDistance(center_) < -radius_) {
		return false;
	}
	return true;
}