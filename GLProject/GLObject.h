#pragma once
#include <vector>
#include"Shader.h"
class GLObject
{
	public:
		GLObject();
		GLObject(glm::vec3 position);
		void CreateCube();
		void CreatePlane();
		unsigned int texture;
		void Draw(Shader& shader);
		void Clear();
		void SetTexture(unsigned int& _texture,Shader& shader);
		void SetPosition(glm::vec3 position);
		unsigned int VAO, VBO, EBO;
	private:	
		
		float* Vertices;
		float* indices;
		int  num;
		
		glm::mat4 model = glm::mat4(1.0f);
};

