#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm\glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 pos_, glm::vec3 color_, float ambient_, float diffuse_);
	~LightSource();
	
	glm::vec3 GetPosition();
	glm::vec3 GetColor();

	float GetAmbient();
	float GetDiffuse();

	void SetPosition(glm::vec3 pos_);
	void SetColor(glm::vec3 color_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);

private:
	glm::vec3 pos;
	glm::vec3 color;
	float ambient, diffuse;
};
#endif