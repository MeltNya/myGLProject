#define GLEW_STATIC
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"Shader.h"

void processInt(GLFWwindow* window);
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "MyGLWindow", NULL, NULL);
    if (window == nullptr) {
        printf("window is null");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("glew failed.");
        glfwTerminate();
        return -1;
    }
    //设置视口绘制区域
    glViewport(0, 0, 800, 600);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //-----------------------------------------------shader complie---------------------------------------------------
    Shader ourShader("vshader.vs", "fshader.fs");

    //--------------------------------------------------vertex---------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);   //产生vao 
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制顶点到缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //设置顶点属性的指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //loop渲染循环
    while (!glfwWindowShouldClose(window))
    {
        //监听事件
        processInt(window);
        //render()
        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.Use();
       // double  timeValue = glfwGetTime();
       // float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
       // int vertexColorLocation = glGetUniformLocation(ourShader.id, "ourColor");
      //  glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
      //  glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
void processInt(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}