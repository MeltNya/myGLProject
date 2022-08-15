#include "Light.h"

void Light::CreateDirectionalLight(glm::vec3 _direction, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _ambient)
	
{
	direction = _direction;
	diffuse = _diffuse;
	specular = _specular;
	ambient = _ambient;
}

void Light::CreatePointLight(glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float c, float l, float q)
{
	position = _position;
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	constant = c;
	linear = l;
	quadratic = q;
}
