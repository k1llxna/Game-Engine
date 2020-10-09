#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"
#include <vector>

class Camera;

class Plane {
public:
	Plane(glm::vec3 normal_, float ogDistance_) : normal(normal_), ogDistance(ogDistance_) {}
	~Plane() {}

	float GetDistance(glm::vec3 pos_) { return glm::dot(normal, pos_) + ogDistance; }

private:
	glm::vec3 normal;
	float ogDistance;
};

class Frustum
{
public:
	Camera* camera;
	Ray viewRay;

	//Plane planes[6][3];
	
	void CreateFrustum();
	bool isSphereInView(glm::vec3 center_, float radius_);

private:

	bool frustum = false;
	std::vector<Plane> frustumPlanes;

	float screenRatio, nearClippingDistance, farClippingDistance;
	glm::vec3 lookAtPos;
};
#endif