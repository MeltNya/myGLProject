#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class Shader {
public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragmentPath);
	void Use() {
		glUseProgram(id);
	}
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
	void setMat4(const std::string& name, glm::mat4 matValue) const
	{
		//	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
		int loc = glGetUniformLocation(id, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matValue));
	}

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};