#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include <GL/glew.h>
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
		string vertexCode, fragmentCode;
		ifstream vShaderFile, fShaderFile;    //ÎÄ¼þstream
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
		catch (ifstream::failure e) {
			std::cout << "Error with shader:faild to  read" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		//----------------compile Shader-------------------

		//create and compile the shader
		unsigned int vertex_shader, fragment_shader;
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
		glCompileShader(vertex_shader);
		checkCompileErrors(vertex_shader, "VERTEX");

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
		glCompileShader(fragment_shader);
		checkCompileErrors(fragment_shader, "FRAGMENT");

		//create shader program and link the shader
		id = glCreateProgram();
		glAttachShader(id, vertex_shader);
		glAttachShader(id, fragment_shader);
		glLinkProgram(id);
		checkCompileErrors(fragment_shader, "PROGRAM");
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
}
//check the shader compile error
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);   
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog 
				<< "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
				<< "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
}