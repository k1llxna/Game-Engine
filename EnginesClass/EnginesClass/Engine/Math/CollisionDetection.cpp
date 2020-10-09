#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection() {}

Ray CollisionDetection::ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_)
{
	glm::vec4 rayStart_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEnd_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView()); // **3D**, use orthgraphic of perspective for 2D

	glm::vec4 rayStart_World = inverse * rayStart_NDC;
	rayStart_World /= rayStart_World.w; // homogonus coords, scales with size

	glm::vec4 rayEnd_World = inverse * rayEnd_NDC;
	rayEnd_World /= rayEnd_World.w;

	glm::vec3 rayDir_World(rayEnd_World - rayStart_World);
	rayDir_World = glm::normalize(rayDir_World);

	return Ray(glm::vec3(rayStart_World), rayDir_World);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x;
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y;

	glm::vec3 obbPosition_World(box_->transform[3].x, box_->transform[3].y, box_->transform[3].z);
	glm::vec3 delta = obbPosition_World - ray_->origin;

	// extract x plane (model mat)
	glm::vec3 xAxis((box_->transform[0].x, box_->transform[0].y, box_->transform[0].z));
	float e = glm::dot(xAxis, delta);
	float f = glm::dot(ray_->direction, xAxis);

	if (fabs(f) > 0.001f) {
		// left intersec check
		float t1 = (e + box_->minVert.x) / f;
		float t2 = (e + box_->maxVert.x) / f;

		if (t1 > t2) { // swap values if t1 is greater (t2 always has to be greater)
			//std::swap(t1, t2);
			float w = t1; t1 = t2; t2 = w;
		}

		if (t2 < tMax) { // tmax is NEAREST FAR interse
			tMax = t2;
		}

		if (t1 > tMin) { // furthest NEAR
			tMin = 1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else { // when rays are almost parallel
		if (-e + box_->minVert.x < 0.0f || -e + box_->maxVert.x < 0.0f) { // x
			return false;
		}
	}

	// y
	//glm::vec3 yAxis((box_->transform[1].x, box_->transform[1].y, box_->transform[1].z));
	//e = glm::dot(yAxis, delta);
	//f = glm::dot(ray_->direction, yAxis);

	//if (fabs(f) > 0.001f) {
	//	// left intersec check
	//	float t1 = (e + box_->minVert.y) / f;
	//	float t2 = (e + box_->maxVert.y) / f;

	//	if (t1 > t2) { // swap values if t1 is greater (t2 always has to be greater)
	//		//std::swap(t1, t2);
	//		float w = t1; t1 = t2; t2 = w;
	//	}

	//	if (t2 < tMax) { // tmax is NEAREST FAR interse
	//		tMax = t2;
	//	}

	//	if (t1 > tMin) { // furthest NEAR
	//		tMin = 1;
	//	}

	//	if (tMax < tMin) {
	//		return false;
	//	}
	//}

	//else { // when rays are almost parallel
	//	if (-e + box_->minVert.y < 0.0f || -e + box_->maxVert.y < 0.0f) { // y
	//		return false;
	//	}
	//}

	//// z
	//glm::vec3 zAxis((box_->transform[2].x, box_->transform[2].y, box_->transform[2].z));
	//e = glm::dot(zAxis, delta);
	//f = glm::dot(ray_->direction, zAxis);

	//if (fabs(f) > 0.001f) {
	//	// left intersec check
	//	float t1 = (e + box_->minVert.z) / f;
	//	float t2 = (e + box_->maxVert.z) / f;

	//	if (t1 > t2) { // swap values if t1 is greater (t2 always has to be greater)
	//		//std::swap(t1, t2);
	//		float w = t1; t1 = t2; t2 = w;
	//	}

	//	if (t2 < tMax) { // tmax is NEAREST FAR interse
	//		tMax = t2;
	//	}

	//	if (t1 > tMin) { // furthest NEAR
	//		tMin = 1;
	//	}

	//	if (tMax < tMin) {
	//		return false;
	//	}
	//}
	//else { // when rays are almost parallel
	//	if (-e + box_->minVert.z < 0.0f || -e + box_->maxVert.z < 0.0f) { // z
	//		return false;
	//	}
	//}

	ray_->intersectionDistance = tMin; // beginning of ray to collisionn
	return true;
}