#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "../FX/LightSource.h"
#include "../Math/Frustum.h"
#include <vector>

class Frustum;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec2 GetClippingPlanes() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetUp() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetWorldUp() const;
	float GetFOV() const;

	void OnDestroy();
	void AddLightSource(LightSource* lightSource_);

	std::vector<LightSource*>GetLightSources() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

	void ChangePos(glm::vec3 newPos_);
	friend Frustum;

private:

	void UpdateCameraVector();
	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView, yaw, pitch, nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lightSources;
};
#endif // !CAMERA_H
