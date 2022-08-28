#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Camera.h"
#include"MyGLHelper.h"
#include"GLProgram.h"
#include"Material.h"
#include"Light.h"
#include"Mesh.h"
#include"Model.h"
#include"GLObject.h"
void processInt(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
float lastX = 400, lastY = 300;
bool firstMouse = true;
Camera camera(
    glm::vec3(0.0f, 0.0f, 5.0f),
    glm::vec3(0.0f, 1.0f, 0.0f), 10.0f, 180.0f
);

int main() {
    GLProgram glProgram;
    glProgram.WindowInit();
    glfwSetCursorPosCallback(glProgram.window, mouse_callback);
    //-----------------------------------------------shader complie---------------------------------------------------
  //  Shader ourShader("vshader2.vs", "light1.fs");
    Shader ourShader("Shader/model.vs", "Shader/model.fs");
    Shader cubeShader("Shader/advanced_opengl/depthTest.vs", "Shader/advanced_opengl/depthTest.fs");
  //  Model ourModel("resources/objects/nanosuit/nanosuit.obj");
    Material ourMat(
        ourShader,
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(1.0f, 0.5f, 0.31f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        32.0f);
    Light dirLight,pointLight;
    dirLight.CreateDirectionalLight(
        glm::vec3(-0.2f, -1.0f, -0.3f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.2f, 0.2f, 0.0f));
    pointLight.CreatePointLight(
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.5f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f, 0.5f, 0.032f
        );

    GLObject obj1;
    obj1.CreateCube();

    unsigned int cubeTexture = MyGLHelper::LoadImage("resources/images/marble.jpg", 0, GL_RGB, GL_RGB);
   // unsigned int floorTexture =

    //loop渲染循环
    while (!glfwWindowShouldClose(glProgram.window))
    {
        //监听事件
        processInt(glProgram.window);
        //render()
        //清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //bind texture
        ourShader.Use();
        ourShader.setMat4("view", camera.GetViewMat());

    // glDeleteVertexArrays(1, &VAO);
     //glDeleteBuffers(1, &VBO);
   //  glDeleteBuffers(1, &EBO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
     //   ourModel.Draw(ourShader);

        //draw cube
       
        obj1.Draw(cubeShader);

        glfwSwapBuffers(glProgram.window);
        glfwPollEvents();
    }
        glfwTerminate();
         return 0;
}

void processInt(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos ) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera.UpdatePY(yoffset, xoffset);
    camera.Rotate();
}