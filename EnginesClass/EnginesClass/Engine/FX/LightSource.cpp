#include "LightSource.h"

LightSource::LightSource(glm::vec3 pos_,glm::vec3 color_, float ambient_, float diffuse_) : pos(pos_), color(color_), ambient(ambient_), diffuse(diffuse_) {}
LightSource::~LightSource() {}

glm::vec3 LightSource::GetPosition()
{
	return pos;
}

glm::vec3 LightSource::GetColor()
{
	return color;
}

float LightSource::GetAmbient()
{
	return ambient;
}

float LightSource::GetDiffuse()
{
	return diffuse;
}

void LightSource::SetPosition(glm::vec3 pos_)
{
	pos = pos_;
}

void LightSource::SetColor(glm::vec3 color_)
{
	color = color_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;	
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}