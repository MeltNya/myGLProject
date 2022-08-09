#pragma once
#include"Camera.h"
class GLProgram {
	public:
		GLProgram(){
		}
		~GLProgram() {

		}
		void WindowInit();
		void Render();
		void CreateObjects();
		void Clear();
		Camera mainCamera;
		GLFWwindow* window;
	private:
};