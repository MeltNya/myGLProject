#pragma once
#include <vector>
#include"Shader.h"
class GLObject
{
	public:
		float* Vertices;
		float* indices;
		int  num;
		void CreateCube();
		unsigned int texture;
		void Draw(Shader shader);
	private:
		unsigned int VAO, VBO, EBO;
		glm::mat4 model;
};

