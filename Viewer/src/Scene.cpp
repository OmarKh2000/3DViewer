#include "Scene.h"
#include "MeshModel.h"
#include <string>



ParallelLight Scene::getParallelLightAtIndex(int i) 
{
	return parallelLights[i-1];

}

PointLight Scene::getPointLightAtIndex(int i)
{
	return pointLights[i-1];

}

void Scene::setDraw(bool t)
{
	this->draw = t;
}

bool Scene::getDraw() const
{
	return draw;
}

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{
	ParallelLight parallelLight;

	this->parallelLights.push_back(parallelLight);

	int i, j;
	float LO = 0;
	float HI = 0.5;
	float r3;

	for (int i = 0; i < 2000 * 2000*5; i++)
	{
		r3 = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		random.push_back(r3);

	}

	PointLight pointLight;
	this->pointLights.push_back(pointLight);
	shadingType = 0;
}
std::vector<float> Scene::getRandom() const
{
	return this->random;

}
void Scene::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shinnies)
{
	models[GetActiveModelIndex()]->SetMaterial(ambient, diffuse, specular, shinnies);
	//this->models[GetActiveModelIndex()]->SetMaterial(ambient, diffuse, specular, shinnies);
	//this->GetActiveModel().SetMaterial(ambient, diffuse, specular, shinnies);
}


void Scene::setSize(glm::vec2 size)
{
	this->size = size;
}



void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
}

void Scene::setshadingType(int T)
{
	this->shadingType = T;
}

int Scene::getshadingType() const
{
	return shadingType;
}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::SetAmbientLightColor(glm::vec4 ambientLightColor)
{
	this->ambientLightColor = ambientLightColor;
}

glm::vec4 Scene::getAmbientLightColor() const
{
	return glm::vec4(this->ambientLightColor);
}

void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

std::vector<ParallelLight> Scene::getParallelLights() const
{
	return this->parallelLights;
}



std::vector<PointLight> Scene::getPointLights() const
{
	return this->pointLights;
}

void Scene::setPointLightAtIndex(PointLight light, int index)
{
	this->pointLights[index - 1] = light;
}



void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::setParallelLightAtIndex(ParallelLight light, int index)
{
	parallelLights[index - 1] = light;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}

void Scene::ScaleActiveModel(float scaleX, float scaleY)
{	if(GetModelCount())
		models[GetActiveModelIndex()]->SetScale(scaleX, scaleY);
}

void Scene::TranslateActiveModel(float x, float y)
{
	if (GetModelCount())
		models[GetActiveModelIndex()]->Translate(x, y);
}

void Scene::setbackgroundcolor(glm::vec4 bgColor)
{
	this->bgColor = bgColor;


}

glm::vec4 Scene::getbackgroundcolor() const
{

	return bgColor;
}

void Scene::RotateActiveModel( float AroundX, float AroundY, float AroundZ)
{
	if (GetModelCount())
		models[GetActiveModelIndex()]->Rotate( AroundX, AroundY, AroundZ);
}

MeshModel Scene::GetActiveModel() const
{
	

	 return *models[GetActiveModelIndex()];

	
	 
}

MeshModel Scene::getModelAtIndex(int i) const
{
	return *models[i];
}

Camera Scene::GetActiveCamera() const
{
	int x = GetActiveCameraIndex();
	return  cameras[GetActiveCameraIndex()];;
}

void Scene::SetdrawNormals(bool drawNormals)
{
	this->drawNormals = drawNormals;

}

void Scene::setBlurAndBloom(int numOfBlurs, bool bloom)
{
	this->bloom = bloom;
	this->blur = numOfBlurs;
}

bool Scene::getBloom() const
{
	return this->bloom;
}

int Scene::getBlur() const
{
	return this->blur;
}

bool Scene::getdrawNormals() const
{
	return drawNormals;

}
bool Scene::getunifromMat() const
{
	return unifromMat;

}
void Scene::setunifromMat(bool unifromMat)
{
	this->unifromMat = unifromMat;

}

void Scene::SetdrawFacesNormals(bool drawFacesNormals) 
{
	this->drawFacesNormals = drawFacesNormals;

}

bool Scene::getdrawFacesNormals() const
{
	return drawFacesNormals;
}

void Scene::SetdrawBox(bool Box)
{
	this->Box = Box;

}

bool Scene::getdrawBox() const
{
	return this->Box;
}

void Scene::setNormalsLength(int normalsLength)
{
	this->normalsLength = normalsLength;
}

void Scene::setFacesNormalsLength(int faceNormalsLength)
{
	this->faceNormalsLength = faceNormalsLength;
}

int Scene::getNoramlsLength() const
{
	return this->normalsLength;
}

int Scene::getFacesNoramlsLength() const
{
	return this->faceNormalsLength;
}

void Scene::setActiveCameraPerspective(float fovy, float aspect,  float Near, float Far)
{	
	if(cameras.size()>0)
		cameras[this->GetActiveCameraIndex()].SetPerspectiveProjection(fovy, aspect, Near, Far);
}

void Scene::setActiveCameraorthographic(float left, float right, float bottom, float top,float Near,float Far)
{
	if (cameras.size() > 0)
		cameras[this->GetActiveCameraIndex()].setCameraorthographic(left, right, bottom, top,Near,Far);
}

glm::mat4x4 Scene::GetActiveCameraProjection() const
{
	if (cameras.size() > 0)
		return cameras[this->GetActiveCameraIndex()].getProjectionTransformation();
	glm::mat4x4 A = glm::mat4x4(1.0);
	return A;
}

void Scene::SetColor(const glm::vec4 & verticesColor, const glm::vec4 & fillingrColor)
{
	(*models[GetActiveModelIndex()]).SetColor(verticesColor, fillingrColor);

}

void Scene::addtParallelLight(const glm::vec3 & direction, const glm::vec3 & color,float ambientCoefficient,float attenuation)
{
	ParallelLight light;
	light.direction = direction;
	light.color = color;
	light.ambientCoefficient = ambientCoefficient;
	light.attenuation = attenuation;
	this->parallelLights.push_back(light);
}

void Scene::AddPointLight(const glm::vec4 & position,   const glm::vec3 & color, const glm::vec3 & coneDirection, float attenuation, float coneAngle )
{

	PointLight light;
	light.position = position;
	light.color = color;
	light.coneDirection = coneDirection;
	light.attenuation = attenuation;
	light.coneAngle = coneAngle;
	this->pointLights.push_back(light);

}



void Scene::setActiveCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{

	cameras[this->GetActiveCameraIndex()].SetCameraLookAt( eye,  at, up);

}
