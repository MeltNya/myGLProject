#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	public:
		void SetCameraPos(glm::vec3 pos);
		Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up);
		Camera(glm::vec3 pos, glm::vec3 world_up, float pitch, float yaw);
		Camera();
		~Camera();
		glm::mat4 GetViewMat();
		void Rotate();
		void UpdatePY(float pitch, float yaw);
	private:
		glm::vec3 Pos;
		glm::vec3 worldUp;
		glm::vec3 cameraForward;		//指向摄像机的z轴正方向
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;
		float cameraPitch, cameraYaw;
		glm::mat4 ViewMat;
		
		void ComputeView();
		
};