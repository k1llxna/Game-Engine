
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm\glm.hpp>

struct BoundingBox {
	glm::vec3 maxVert, minVert;
	glm::mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = glm::vec3();
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 boxMinCorner = GetTransformedPoint(box_->minVert, box_->transform);
		glm::vec3 boxMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		return 
		(minCorner.x <= boxMaxCorner.x && maxCorner.x >= boxMinCorner.x) && 
		(minCorner.y <= boxMaxCorner.y && maxCorner.y >= boxMinCorner.y) &&
		(minCorner.z <= boxMaxCorner.z && maxCorner.z >= boxMinCorner.z);
	}

private:
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_;
	}
};
#endif // !BOUNDINGBOX_H
