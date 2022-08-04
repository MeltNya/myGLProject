#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
class MyGLHelper
{
public:
	MyGLHelper();
	~MyGLHelper();
	static unsigned int  LoadImage(const char* path, int textureNum, GLint internalFormat, GLint format) {
        unsigned int texBuffer;
        glGenTextures(1, &texBuffer);
        glActiveTexture(GL_TEXTURE0 + textureNum);
        glBindTexture(GL_TEXTURE_2D, texBuffer);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
       // stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "Succeed to load texture" << std::endl;
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        return texBuffer;
	 }
private:

};

MyGLHelper::MyGLHelper()
{
}

MyGLHelper::~MyGLHelper()
{
}