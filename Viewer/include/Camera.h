#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera
{
private:
	glm::mat4x4 viewTransformation;
	glm::mat4x4 projectionTransformation;
	float zoom;
	glm::vec4 eye;
	glm::vec4 at;
	glm::vec4 up;

public:
	//Camera(Camera camera);
	Camera();
	Camera(const glm::vec4& eye , const glm::vec4& at , const glm::vec4& up );
	~Camera();
	Camera& operator=(const Camera &other);
	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

	void SetOrthographicProjection(
		const float height,
		const float aspectRatio,
		const float near,
		const float far);

	void SetPerspectiveProjection(
		const float fovy,
		const float aspectRatio,
		const float near,
		const float far);

	void SetZoom(const float zoom);
	float getZoom() const;

	glm::mat4x4 getviewTransformation() const;
	glm::mat4x4	getProjectionTransformation() const;
	void setCameraorthographic(float left, float right, float bottom, float top,float Near,float Far);
	glm::vec4 getEye() const;
	glm::vec4 getUp() const;
	glm::vec4 getAt() const;

};
