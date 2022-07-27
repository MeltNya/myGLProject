#include"Camera.h"

Camera::Camera() {
	Pos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraForward = glm::normalize(glm::vec3(0.0f,0.0f,0.0f)-Pos);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	ComputeView();
}
Camera::~Camera(){

}
Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up) {
	Pos = pos;
	worldUp = world_up;
	cameraForward = glm::normalize(target - pos);
	cameraRight = glm::normalize( glm::cross(cameraForward, worldUp));
	cameraUp = glm::normalize(glm::cross(worldUp, cameraRight));
	ComputeView();
}
Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up, glm::vec3 pitch, glm::vec3 yaw) {
	Pos = pos;
	worldUp = world_up;
	//cameraForward.x =cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}

void Camera::ComputeView() {
	ViewMat = glm::lookAt(Pos,Pos+cameraForward,worldUp);
}
void Camera::SetCameraPos(glm::vec3 pos) {
	Pos = pos;
	ComputeView();
}
glm::mat4 Camera::GetViewMat() {
	return ViewMat;
}