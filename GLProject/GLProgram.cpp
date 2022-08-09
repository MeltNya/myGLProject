#pragma once
#include"GLProgram.h"
#include <GL/glew.h>
void GLProgram::WindowInit() {
    glfwInit();
    float screenWidth = 800;
    float screenHeight = 600;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //创建窗口
    window = glfwCreateWindow(800, 600, "MyGLWindow", NULL, NULL);
    if (window == nullptr) {
        printf("window is null");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("glew failed.");
        glfwTerminate();
       // return -1;
    }
    //设置视口绘制区域
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
	
}
void GLProgram::CreateObjects() {

}
void GLProgram::Render() {

}