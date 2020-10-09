#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

//#include "../Camera/Camera.h"
#include <glm\glm.hpp>

// only used for DATA TYPES
struct Ray;
struct BoundingBox; 

class Camera;

class CollisionDetection {
public:
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;

	CollisionDetection() = delete; // remove contructor
	~CollisionDetection();

	static Ray ScreenPosToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);
};
#endif