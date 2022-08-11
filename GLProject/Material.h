#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
class Material
{
public:
    Shader* shader;
    glm::vec3 ambient;       //��������ɫ
    glm::vec3 diffuse;         //��������ɫ
    glm::vec3 specular;      //�߹���ɫ
    float shininess;            //�߹�뾶
    Material(Shader* shader, glm::vec3 _ambient, glm::vec3 _diffuse,glm::vec3 _specular, float _shininess);
    Material();
    void SetFloat(const std::string& name, bool value);
    void SetVec3(const std::string& name, glm::vec3 vec);
private:

};

