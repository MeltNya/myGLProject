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
    glEnable(GL_DEPTH_TEST);                                         //开启深度测试
    glDepthFunc(GL_LESS);                                               //深度值小于缓冲时通过测试
    glEnable(GL_STENCIL_TEST);                                      //开启模板测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);                     //模板参考值=1将通过
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glfwSetCursorPosCallback(glProgram.window, mouse_callback);
    //-----------------------------------------------shader complie---------------------------------------------------
    
    Shader ourShader("Shader/model.vs", "Shader/model.fs");
    Shader cubeShader("Shader/advanced_opengl/depthTest.vs", "Shader/advanced_opengl/depthTest.fs");
    Shader normalShader("Shader/advanced_opengl/stencilTest.vs", "Shader/advanced_opengl/stencilTest.fs");
    Shader outlineShader("Shader/advanced_opengl/stencilTest.vs", "Shader/advanced_opengl/stencil_outline.fs");
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
    unsigned int cubeTexture = MyGLHelper::loadImageA("resources/images/marble.jpg");
    unsigned int floorTexture = MyGLHelper::loadImageA("resources/images/metal.png");

    GLObject obj1,obj2;
    obj1.CreateCube();
    obj1.SetPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
    //obj1.SetTexture(cubeTexture,stencilShader);
    normalShader.Use();
    normalShader.setInt("texture1", 0);
    obj2.CreateCube();
    obj2.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    normalShader.Use();
    normalShader.setInt("texture1", 0);
    //obj2.SetTexture(cubeTexture, stencilShader);
    GLObject floor;
    floor.CreatePlane();
    floor.SetTexture(floorTexture, cubeShader);
    //loop渲染循环
    while (!glfwWindowShouldClose(glProgram.window))
    {
        //监听事件
        processInt(glProgram.window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);   //    clear the color and depth buffer

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        outlineShader.Use(); 
        outlineShader.setMat4("projection", projection);
        outlineShader.setMat4("view", camera.GetViewMat());
        normalShader.Use();
        normalShader.setMat4("view", camera.GetViewMat());
        normalShader.setMat4("projection", projection);

        //draw floor as normal
        glStencilMask(0x00);
        glBindVertexArray(floor.VAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        normalShader.setMat4("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        // draw objects as normal;
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        glBindVertexArray(obj1.VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        normalShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        normalShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

       //draw outline, this time disabling stencil writing.
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        outlineShader.Use();
        float scale = 1.1f;
        glBindVertexArray(obj1.VAO);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);;
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        outlineShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        outlineShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
       
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
        //swap buffer
        glfwSwapBuffers(glProgram.window);
        glfwPollEvents();
    }
    obj1.Clear();
    floor.Clear();
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