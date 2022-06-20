#pragma once
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include <GL/glew.h>
using namespace std;
class Shader {
public:
	unsigned int id;
	Shader(const char* vertexPath, const char* fragmentPath) {
		string vertexCode, fragmentCode;
		ifstream vShaderFile, fShaderFile;
		//-----read shader file
		//exceptions
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			//open the shader file and convert data to stringStream
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(ifstream::failure e){
			std::cout << "error with shader:faild to  read" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//compile Shader
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		fragment= glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(fragment, 1, &vShaderCode, NULL);
		glCompileShader(fragment);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader Program
		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		// print linking errors if any
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Use() {
		glUseProgram(id);
	}
	void SetBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation( id, name.c_str() ), (int)value);
	}
	void SetInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation( id, name.c_str() ), value);
	}
	void SetFloat(const std::string& name, float value) const {
		glUniform1i(glGetUniformLocation( id, name.c_str() ), value);
	}
	//void SetFloat(const std::string& name, ) const {
	//	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	//}
};