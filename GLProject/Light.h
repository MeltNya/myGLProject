#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
	public:
		glm::vec3 direction;
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 ambient;
		glm::vec3 specular;
		
		float constant;
		float linear;
		float quadratic;
		void CreateDirectionalLight(glm::vec3 _direction, glm::vec3 _diffuse, glm::vec3 _specular,glm::vec3 _ambient );
		void CreatePointLight(glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float c, float l, float q);
	private:

};

