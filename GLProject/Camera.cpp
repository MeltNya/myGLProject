#include"Camera.h"
#include <iostream>

Camera::Camera() {
	Pos = glm::vec3(0.0f, 0.0f, 3.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
Camera::Camera(glm::vec3 pos,  glm::vec3 world_up, float pitch,float yaw) {
	Pos = pos;
	worldUp = world_up;
	cameraPitch = pitch;
	cameraYaw = yaw;
	cameraForward.x =glm::cos( glm::radians( pitch) ) * glm::sin(glm::radians(yaw) );
	cameraForward.y =glm:: sin( glm::radians(pitch) );
	cameraForward.z =glm:: cos( glm::radians(pitch) ) * cos( glm::radians(yaw) );
	cameraForward = glm::normalize(cameraForward);
	cameraRight = glm::normalize(glm::cross(cameraForward, worldUp));
	cameraUp = glm::normalize(glm::cross(worldUp, cameraRight));
	ComputeView();
}

void Camera::ComputeView() {
	ViewMat = glm::lookAt(Pos,Pos+cameraForward,worldUp);
}
void Camera::SetCameraPos(glm::vec3 pos) {
	Pos = pos;
	ComputeView();
}
void Camera::Rotate() {
	if (cameraPitch > 89.0f)
		cameraPitch = 89.0f;
	if (cameraPitch < -89.0f)
		cameraPitch = -89.0f;
	cameraForward.x = glm::cos(glm::radians(cameraPitch)) * glm::sin(glm::radians(cameraYaw));
	cameraForward.y = glm::sin(glm::radians(cameraPitch));
	cameraForward.z = glm::cos(glm::radians(cameraPitch)) * cos(glm::radians(cameraYaw));
	cameraForward = glm::normalize(cameraForward);
	cameraRight = glm::normalize(glm::cross(cameraForward, worldUp));
	cameraUp = glm::normalize(glm::cross(worldUp, cameraRight));
	ComputeView();
	//std::cout << "camera move" <<std ::endl;
}
void Camera::UpdatePY(float pitchOffset, float yawOffset) {
	cameraPitch += pitchOffset;
	cameraYaw += yawOffset;
}
glm::mat4 Camera::GetViewMat() {
	return ViewMat;
}