#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	Material() :ambient(glm::vec3(0.71764, 0.5803, 0.2235)), diffuse(glm::vec3(0.71764, 0.5843, 0.23524)), specular(glm::vec3(0.0823, 0.07843, 0.0705)), shininess(0.4)
	{}
	//Material():ambient(glm::vec3(0.24725, 0.1995, 0.0745)), diffuse(glm::vec3(0.75164, 0.60648, 0.22648)), specular(glm::vec3(0.628281, 0.555802, 0.465686262 )),shininess(0.4)
	//{}
};
class MeshModel 
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform;
	glm::vec4 fillingrColor;
	glm::vec4 verticesColor;
	std::string modelName;
	friend class Renderer;
	float scaleX;
	float scaleY;
	float TranslateX;
	float TranslateY;
	float Aroundx, AroundY, AroundZ;
	bool drawBox;
	bool drawNormals;
	bool drawFacesNormals;
	std::vector<glm::vec3> Box;
	Material material;
public:

	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();
	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;
	void setDrawing(bool drawBox, bool drawNormals, bool drawFacesNormals);
	bool getDrawBox() const;
	bool getDrawNormals() const;
	bool getdrawFacesNormals() const;
	const glm::vec4& getverticesColor() const;
	const glm::vec4& getfillingrColor() const;
	void SetColor(const glm::vec4& verticesColor, const glm::vec4& fillingrColor);
	void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	Material getMaterial() const;
	const std::string& GetModelName();
	std::vector<glm::vec3> getBox();
	void SetScale(float scaleX, float scaleY);
	void Translate(float x, float y);
	void Rotate(float AroundX,float AroundY,float AroundZ);
	// Add more methods/functionality as needed...
};
