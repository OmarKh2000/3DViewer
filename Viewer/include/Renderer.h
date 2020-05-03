#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
/*
 * Renderer class.
 */
class Renderer :public Scene
{
private:
	float *colorBuffer;
	//float *zBuffer=NULL;
	
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;
	friend class MeshModel;
	void putPixel(int x, int y, const glm::vec3& color) const;
	void createBuffers(int viewportWidth, int viewportHeight);
	//glm::vec3 colorBuffer[1920][1001];
	//float zBuffer[1920][1001];


	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();

	void Render(const Scene& scene);
	void unifromMat(const Scene & scene, float * buffer);
	//void unifromMat(float * buffer);
	void Bloom(const Scene & scene, float * buffer);
	float * bloom_light(float * image);
	void blurScreen(float * buffer, bool print);
	void drawBox(std::vector<glm::vec3> box, MeshModel model, const Scene & scene, glm::vec3 color);
	void SwapBuffers();
	void drawLine(const glm::vec3 point0, const glm::vec3 point1, const std::vector<glm::vec3>* points,  const std::vector<glm::vec3>* normals, const MeshModel &model, const Scene & scence, int shadingType, glm::vec3 color, glm::mat3x3 scaleMatrix) const;
	void drawLine2(const glm::vec3 point0, const glm::vec3 point1, const glm::vec3 normalP0, const glm::vec3 normalP1, Material material, const Scene & scence, int shadingType, glm::vec3 color) const;
	void drawTriangles(const std::vector<glm::vec3>* points, const std::vector<glm::vec3>* normals,  const Scene & scene, const MeshModel &model, glm::mat3x2 scaleMatrix);
	float area(int x1, int y1, int x2, int y2, int x3, int y3) const;
	bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) const;
	int ReScaleX(float num, glm::mat3x2 scaleMatrix);
	int ReScaleY(float num, glm::mat3x2 scaleMatrix);
	int ReScaleZ(float num, glm::mat3x2 scaleMatrix);
	glm::vec3 ReScale(glm::vec3 & v, glm::mat3x2 scaleMatrix);
	glm::vec3 Scale(glm::vec3 & v) const;
	void fillBottomFlatTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normalP1, glm::vec3 normalP2, glm::vec3 normalP3, const Scene & scene, Material material, bool drawFacesNormal, int shadingType);
	void fillTopFlatTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normalP1, glm::vec3 normalP2, glm::vec3 normalP3, const Scene & scene, Material material, bool drawFacesNormal, int shadingType);
	glm::vec3 calculatepointLight(const glm::vec3 vertex, const glm::vec3 normal, Material material, PointLight light) const;
	glm::vec3 getcolor(const glm::vec3 vertex, const glm::vec3 normal, Material material, const Scene & scene) const;
	glm::vec3 calculateParallelLight(const glm::vec3 vertex, const glm::vec3 normal, Material material, ParallelLight light) const;
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void drawModel(const Scene & scene, const MeshModel & model);

	//void putPixel2(int i, int j, const glm::vec3& color);

	// write function that takes a model and draw it
	// Add more methods/functionality as needed...
};

