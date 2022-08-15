#include "Material.h"

Material::Material(Shader* _shader ,glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess):
	shader(_shader), ambient(_ambient), diffuse(_diffuse),specular(_specular),shininess(_shininess)
{ }

Material::Material(Shader * _shader, unsigned int _diffuse, unsigned int _specular):
	shader(_shader),diffuseMap(_diffuse),specularMap(_specular)
{
}

Material::Material() {

}

Material::~Material()
{
}

void Material::SetFloat(const std::string& name, bool value)
{
	shader->setBool(name, value);
}

void Material::SetVec3(const std::string& name, glm::vec3 vec)
{
	shader->setVec3(name, vec);
}

void Material::SetVec3(const std::string& name, float x, float y, float z)
{
	shader->setVec3(name, x, y, z);
}

void Material::SetMat4(const std::string& name, glm::mat4 matValue)
{
	shader->setMat4(name, matValue);
}

