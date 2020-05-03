#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"

struct ParallelLight
{
	glm::vec3 direction;
	glm::vec3 color;
	float ambientCoefficient;
	float attenuation;
	ParallelLight():direction(glm::vec3(1, 0.8, 0.6)), color(glm::vec3(1, 1, 1)), ambientCoefficient(1), attenuation(1)
	{}
};
struct PointLight
{
	glm::vec4 position;
	glm::vec3 color;
	glm::vec3 coneDirection;
	float attenuation;
	float coneAngle;
	PointLight ():position(glm::vec4(0, 0, 3,1)), color(glm::vec3(0.3f, 0.2f, 0.3f)), coneDirection(glm::vec3(0, 0, 0)), attenuation(0.0f), coneAngle(15.0f)
	{}
};


/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
enum shadingType { flat, gouraud, Phong };

class Scene {
private:
	bool unifromMat = false;

	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<ParallelLight> parallelLights;
	std::vector<PointLight> pointLights;
	//std::vector<Light> Lights;
	int shadingType;
	std::vector<Camera> cameras;
	bool drawNormals = false;
	bool bloom=false;
	std::vector<float> random;
	int blur = 0;
	int activeCameraIndex;
	int activeModelIndex;
	bool drawFacesNormals = false;
	bool Box = false;
	glm::vec4 bgColor;
	int normalsLength = 10;
	int faceNormalsLength = 10;
	glm::vec2 size;
	glm::vec4 ambientLightColor ;
	bool draw=true;
public:
	ParallelLight getParallelLightAtIndex(int i);
	PointLight getPointLightAtIndex(int i);
	void setDraw(bool t);
	bool getDraw() const;
	Scene();
	std::vector<float> getRandom() const;
	void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shinnies);
	//void addLight(glm::vec4 position, glm::vec3 color, float attenuation, float ambientCoefficient, float coneAngle,glm::vec3 coneDirection,bool isOn);
	void setSize(glm::vec2 size);
	void AddModel(const std::shared_ptr<MeshModel>& model);
	void setshadingType(int T);
	int getshadingType() const;
	const int GetModelCount() const;
	void SetAmbientLightColor(glm::vec4 ambientLightColor);
	glm::vec4 getAmbientLightColor() const;
	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;
	std::vector<ParallelLight> getParallelLights() const;
	std::vector<PointLight> getPointLights() const;
	void setPointLightAtIndex(PointLight light, int index);
	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;
	void setParallelLightAtIndex(ParallelLight light, int index);
	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;
	void ScaleActiveModel(float scaleX, float scaleY);
	void TranslateActiveModel(float x, float y);
	void setbackgroundcolor(glm::vec4 bgColor);
	glm::vec4 getbackgroundcolor() const;
	void RotateActiveModel( float AroundX, float AroundY, float AroundZ);
	  MeshModel GetActiveModel() const ;
	  MeshModel getModelAtIndex(int i) const;
	  Camera GetActiveCamera() const;
	  void SetdrawNormals(bool drawNormals);
	  void setBlurAndBloom(int numOfBlurs, bool bloom);
	  bool getBloom() const;
	  int getBlur() const;
	  bool getdrawNormals() const;
	  bool getunifromMat() const;
	  void setunifromMat(bool unifromMat);
	  void SetdrawFacesNormals(bool drawFacesNormals);
	  bool getdrawFacesNormals() const;
	  void SetdrawBox(bool Box);
	  bool getdrawBox() const;
	  void setNormalsLength(int normalsLength);
	  void setFacesNormalsLength(int faceNormalsLength);
	  int getNoramlsLength() const;
	  int getFacesNoramlsLength() const;
	  void setActiveCameraPerspective(float fovy, float aspect, float Near, float Far);
	  void setActiveCameraorthographic(float left, float right, float bottom, float top,float Near,float Far);
	  glm::mat4x4 GetActiveCameraProjection() const;
	  void SetColor(const glm::vec4& verticesColor, const glm::vec4& fillingrColor);
	  void addtParallelLight(const glm::vec3 & direction, const glm::vec3 & color, float ambientCoefficient, float attenuation);
	  void AddPointLight(const glm::vec4 & position, const glm::vec3 & color, const glm::vec3 & coneDirection, float attenuation, float coneAngle);
	  //void setParallelLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,bool isOn);
	 // void AddPointLight(const glm::vec3& position, float constant, float linear , float quadratic  , const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, bool isOn);
	  void setActiveCameraLookAt(const glm::vec3 & eye, const glm::vec3 & at, const glm::vec3 & up);



};