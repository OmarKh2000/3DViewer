#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

#define screenWidth 1280
#define screenHeight 720
/* Camera class defualt construct*/
Camera::Camera():eye(glm::vec4(0, 0, 1.0, 0)),at(glm::vec4(0, 0, 0, 0)),up(glm::vec4(0, 1.0, 0, 0))
{
	viewTransformation = glm::mat4(1.0);
	projectionTransformation = glm::mat4(1.0);
	eye = glm::vec4(0, 0, 1.0, 0);
	at = (glm::vec4(0, 0, 0, 0));
	up = glm::vec4(0, 1.0, 0, 0);
	
}

/* Camera class  construct*/
Camera::Camera(const glm::vec4& eye , const glm::vec4& at , const glm::vec4& up ) :	zoom(1.0),  eye(glm::vec4(eye)), at(glm::vec4(at)), up(glm::vec4(up))
{
	viewTransformation = glm::mat4(1.0);
	projectionTransformation = glm::mat4(1.0);
	SetCameraLookAt(eye, at, up);
	this->eye = eye;
	this->at = at;
	this->up = up;
}

Camera::~Camera()
{
}


Camera & Camera::operator=(const Camera & other)
{
	this->eye = glm::vec4(other.getEye());
	this->up = glm::vec4(other.getUp());
	this->at = glm::vec4(other.getAt());
	this->viewTransformation = other.getviewTransformation();
	this->projectionTransformation = other.getProjectionTransformation();
	return *this;
}

/*function responsible of camera transfomations*/
void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{


	this->eye = glm::vec4(eye,0);
	this->at = glm::vec4( at,0 );
	this->up = glm::vec4(up, 0);



	glm::vec3 forward = normalize(eye - at);
	glm::vec3 right = cross(normalize(up), forward);
	glm::vec3 up2 = cross(forward, right);
	viewTransformation[0][0] = right.x;	/*Setting the view matrix, Format is taken from OpenGL*/
	viewTransformation[0][1] = right.y;
	viewTransformation[0][2] = right.z;
	viewTransformation[1][0] = up2.x;
	viewTransformation[1][1] = up2.y;
	viewTransformation[1][2] = up2.z;
	viewTransformation[2][0] = forward.x;
	viewTransformation[2][1] = forward.y;
	viewTransformation[2][2] = forward.z;
	viewTransformation[3][0] = eye.x;
	viewTransformation[3][1] = eye.y;
	viewTransformation[3][2] = eye.z;
}


void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{
	float x = screenWidth / screenHeight;
	projectionTransformation = glm::perspective(fovy, x, near, far);
	const float ar = screenWidth / screenHeight;
	const float zNear = near;
	const float zFar = far;
	const float zRange = near - far;
	const float tanHalfFOV = tanf(glm::radians(fovy / 2.0));

	projectionTransformation[0][0] = 1.0f / (tanHalfFOV * ar);	/*Setting the projection matrix, Foramt is taken from OpenGL*/ 
	projectionTransformation[0][1] = 0.0f;
	projectionTransformation[0][2] = 0.0f;
	projectionTransformation[0][3] = 0.0f;

	projectionTransformation[1][0] = 0.0f;
	projectionTransformation[1][1] = 1.0f / tanHalfFOV;
	projectionTransformation[1][2] = 0.0f;
	projectionTransformation[1][3] = 0.0f;

	projectionTransformation[2][0] = 0.0f;
	projectionTransformation[2][1] = 0.0f;
	projectionTransformation[2][2] = (-zNear - zFar) / zRange;
	projectionTransformation[2][3] = 2.0f * zFar * zNear / zRange;

	projectionTransformation[3][0] = 0.0f;
	projectionTransformation[3][1] = 0.0f;
	projectionTransformation[3][2] = 1.0f;
	projectionTransformation[3][3] = 0.0f;

}	

void Camera::SetZoom(const float zoom) //	Set camera zoom
{
	this->zoom = zoom;
}

float Camera::getZoom() const	// Get camera zoom
{
	return zoom;
}

glm::mat4x4 Camera::getviewTransformation() const
{
	return glm::mat4x4(viewTransformation);
}

glm::mat4x4 Camera::getProjectionTransformation() const
{
	glm::mat4x4 A= projectionTransformation;
	return A;
}

void Camera::setCameraorthographic(float left, float right, float bottom, float top,float Near,float Far)
{
	
	projectionTransformation[0][0] = 2 / (right - left); /*Setting projection matrix as orthographic, format taken from OpenGL*/
	projectionTransformation[0][1] = 0;
	projectionTransformation[0][2] = 0;
	projectionTransformation[0][3] = 0;

	projectionTransformation[1][0] = 0;
	projectionTransformation[1][1] = 2 / (top - bottom);
	projectionTransformation[1][2] = 0;
	projectionTransformation[1][3] = 0;

	projectionTransformation[2][0] = 0;
	projectionTransformation[2][1] = 0;
	projectionTransformation[2][2] = -2 / (Far - Near);
	projectionTransformation[2][3] = 0;

	projectionTransformation[3][0] = -(right + left) / (right - left);
	projectionTransformation[3][1] = -(top + bottom) / (top - bottom);
	projectionTransformation[3][2] = -(Far + Near) / (Far - Near);
	projectionTransformation[3][3] = 1;


}

glm::vec4 Camera::getEye() const
{
	return  (glm::vec4(eye));
}

glm::vec4 Camera::getUp() const
{
	return  (glm::vec4(up));
}

glm::vec4 Camera::getAt() const
{
	return  (glm::vec4(at));;
}

