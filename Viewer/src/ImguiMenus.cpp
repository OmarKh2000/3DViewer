#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>
#define lightScale 1000
float AroundX = 0;
float AroundY = 0;
float AroundZ = 0;
float AroundXModel = 0;
float AroundYModel = 0;
float AroundZModel = 0;
bool showDemoWindow = false;
bool showAnotherWindow = false;
bool drawNormals = false;
bool drawFacesNormals = false;
bool bloom = false;
int camera = 0;
bool Box;
bool unifromMat = false;
bool perspective=true;
bool orthographic=false;
int normalsLength=5;
int faceNormalsLength=5;
float fovy = 10, aspect = 1.0, Near = -10, Far =20;
float left = -3, right = 3, bottom = -3, top = 3, Near2 = 0.1, Far2 = 200;
float zoom = 2.0;
Material activeModelMaterial;
glm::vec4 eye = { 0,0,1,0 }, at= { 0,0,0,0 }, up= { 0,0,0,0 };
glm::vec4 clearColor = glm::vec4(0.127697125f, 0.519607842f, 0.0891484097f, 1.00f);
int parallelLightCounter = 1;
int pointLightCounter = 1;

int shadingType = 0;
ParallelLight activeParallelLight;
PointLight activePointLight;
int prevCamera = 1;
const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
	glm::vec2 size;
	/*size.push_back(io.DisplaySize.x);
	size.push_back(io.DisplaySize.y);*/

	//scene.setSize(size);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 1;
		
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		
		if (perspective)
		{
		
			scene.setActiveCameraPerspective(fovy, aspect, Near, Far);
		}
		scene.GetActiveCamera().SetZoom(zoom);

		if (ImGui::CollapsingHeader("View setting"))
		{/* View control*/

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color
			scene.setbackgroundcolor(clearColor);
			ImGui::Checkbox("perspective", &perspective);
			if (perspective)
			{
				orthographic = false;

				ImGui::SliderFloat("fovy", &fovy, -1, 10);
				ImGui::SliderFloat("near", &Near, -1000, 10);
				ImGui::SliderFloat("far", &Far, 0, 2000);

				scene.setActiveCameraPerspective(fovy, aspect, Near, Far);
			}

			ImGui::Checkbox("Orthographic ", &orthographic);
			if (orthographic)
			{
				perspective = false;
				ImGui::SliderFloat("left ", &left, -10, 10);
				ImGui::SliderFloat("right", &right, -10, 10);
				ImGui::SliderFloat("bottom", &bottom, -10, 10);
				ImGui::SliderFloat("top", &top, -10, 10);
				ImGui::SliderFloat("near", &Near2, 0, 200);
				ImGui::SliderFloat("far", &Far2, 0, 200);

				scene.setActiveCameraorthographic(left, right, bottom, top, Near2, Far2);
			}
			ImGui::SliderFloat("zoom", &zoom, 1, 10);
			scene.GetActiveCamera().SetZoom(zoom);

		}

		
		float x1=0, x2=0, x3=0;

 		if (ImGui::CollapsingHeader("Camera setting"))
		{ /* Camera controls*/
			static int i5 = 1;
			ImGui::SliderFloat("Camera X Position:", &eye.x, -1, 10);
			ImGui::SliderFloat("Camera Y Position:", &eye.y, -1, 10);
			ImGui::SliderFloat("Camera Z Position:", &eye.z, -10, 40);


			ImGui::SliderFloat("Camera Looking Up X:", &up.x, -1, 10);
			ImGui::SliderFloat("Camera Looking Up y:", &up.y, -1, 10);
			ImGui::SliderFloat("Camera Looking Up Z:", &up.z, -1, 10);

			ImGui::SliderFloat("Camera Looking At X:", &at.x, -1, 10);
			ImGui::SliderFloat("Camera Looking At Y:", &at.y, -1, 10);
			ImGui::SliderFloat("Camera Looking At Z", &at.z, -1, 10);
		
			if (ImGui::Button("Add camera"))
			{
				counter++;
				scene.AddCamera(Camera(eye,at,up));
			}
			if (ImGui::Button("Reset"))
			{
				eye = { 0, 0, 1, 0 };
				at = { 0, 0, 0, 0 };
				up = { 0, 1, 0, 0 };
			}


			ImGui::SameLine();
			ImGui::Text("Cameras # = %d", counter);
			static int i1 = 1;
			ImGui::SliderInt("Choose camera", &i1, 1, scene.GetCameraCount());
			scene.SetActiveCameraIndex(i1-1);
			if (i1 != prevCamera)
			{
				eye = scene.GetActiveCamera().getEye();
				at = scene.GetActiveCamera().getAt();
				up = scene.GetActiveCamera().getUp();
				prevCamera = i1;
			}
			
			//scene.SetActiveCameraIndex(i1);
			if(i5==1)
				scene.setActiveCameraLookAt(eye, glm::vec3(0,0,0), up);
			else
				scene.setActiveCameraLookAt(eye, at, up);
			static int i2 = 0;
		}

		static float scaleX = 1;
		static float scaleY = 1;
		static float TranslateX =-1;
		static float TranslateY = -1;
		static float TranslateXModel = 0;
		static float TranslateYModel = 0;
		scene.ScaleActiveModel(scaleX+zoom/10, scaleY+zoom/10);
		scene.TranslateActiveModel(TranslateX, TranslateY);
		if (ImGui::CollapsingHeader("Object setting"))
		{	/*Object control*/
			static int i6 = 1;

			static int i2 = 1;
			ImGui::SliderInt("Choose Model", &i2, 1, scene.GetModelCount());
			scene.SetActiveModelIndex(i2 - 1);
			if (scene.GetModelCount()) {
				activeModelMaterial = scene.GetActiveModel().getMaterial();
			}
			ImGui::SliderFloat("scaleX", &scaleX, 0.01, 10);
			ImGui::SliderFloat("scaleY", &scaleY, 0.01, 10);
			scene.ScaleActiveModel(scaleX+zoom/10, scaleY+zoom/10);	
			
			ImGui::Text("Model frame:");
			ImGui::SliderFloat("TranslateX", &TranslateX, -5, 5);		
			ImGui::SliderFloat("TranslateY", &TranslateY, -5, 5);

			ImGui::SliderFloat("RoateAroundX", &AroundX, -180, 180);
			ImGui::SliderFloat("RotateAroundY", &AroundY, -180, 180);
			ImGui::SliderFloat("RotateAroundZ", &AroundZ, -180, 180);

			scene.TranslateActiveModel(TranslateX+ TranslateXModel+2, TranslateY+ TranslateYModel+2);
			scene.RotateActiveModel(glm::radians(AroundX+ AroundXModel), glm::radians(AroundY+ AroundYModel), glm::radians(AroundZ+ AroundZModel));

			ImGui::ColorEdit3("ambient color", (float*)&activeModelMaterial.ambient);
			ImGui::ColorEdit3("diffuse color", (float*)&activeModelMaterial.diffuse);
			ImGui::ColorEdit3("specular color", (float*)&activeModelMaterial.specular);
			ImGui::SliderFloat("material shininess ",&activeModelMaterial.shininess, 0.01, 1);
			if (activeModelMaterial.shininess > 0.5)
				int a = 5;

			if (scene.GetModelCount())
				scene.SetMaterial(activeModelMaterial.ambient, activeModelMaterial.diffuse, activeModelMaterial.specular, activeModelMaterial.shininess);

			ImGui::Checkbox("Draw Normals", &drawNormals);
			scene.SetdrawNormals(drawNormals);
			ImGui::SliderInt("Set Normals Length", &normalsLength, 1, 200);
			scene.setNormalsLength(normalsLength);
			ImGui::Checkbox("Draw Faces Normals", &drawFacesNormals);
			scene.SetdrawFacesNormals(drawFacesNormals);
			ImGui::SliderInt("Set Normals Length", &faceNormalsLength, 1, 200);
			scene.setFacesNormalsLength(faceNormalsLength);
			scene.SetdrawBox(Box);

		}



		if (ImGui::Button("draw"))
		{
			bool draw=!scene.getDraw();
			scene.setDraw(draw);
		}
		static int i3 = 1;
		static int i4 = 1;
		static int i5 = 0;
		activeParallelLight = scene.getParallelLightAtIndex(i3);
		activePointLight = scene.getPointLightAtIndex(i4);
		activePointLight.position = activePointLight.position / float(lightScale);

		if (ImGui::CollapsingHeader("Light setting"))
		{
			



			ImGui::SliderInt("Choose Shading Type", &shadingType, 0, 2);
			scene.setshadingType(shadingType);

			ImGui::SliderFloat("Light X Direction:", &activeParallelLight.direction.x, -1, 10);
			ImGui::SliderFloat("Light Y Direction:", &activeParallelLight.direction.y, -1, 10);
			ImGui::SliderFloat("Light Z Direction:", &activeParallelLight.direction.z, -1, 10);
			ImGui::ColorEdit3("Light color", (float*)&activeParallelLight.color);
			ImGui::SliderFloat("ParallelambientCoefficient", &activeParallelLight.ambientCoefficient, 0, 5);
			ImGui::SliderFloat("Parallelattenuation", &activeParallelLight.attenuation, 0, 5);
			scene.setParallelLightAtIndex(activeParallelLight, i3);
			if (ImGui::Button("Add Parallel Light"))
			{
				scene.addtParallelLight(activeParallelLight.direction, activeParallelLight.color, activeParallelLight.ambientCoefficient, activeParallelLight.attenuation);
				parallelLightCounter++;
			}
			ImGui::SliderInt("Choose Paralle lLight", &i3, 1, parallelLightCounter);


		
			ImGui::SliderFloat("Light X Position:", &activePointLight.position.x, -1, 1);
			ImGui::SliderFloat("Light Y Position:", &activePointLight.position.y, -1, 1);
			ImGui::SliderFloat("Light Z Position:", &activePointLight.position.z, -1, 1);
			activePointLight.position = activePointLight.position * float(lightScale);
			ImGui::SliderFloat("Cone Angle:", &activePointLight.coneAngle, 0, 180);
			ImGui::SliderFloat("Cone X Direction:", &activePointLight.coneDirection.x, -1, 1);
			ImGui::SliderFloat("Cone Y Direction:", &activePointLight.coneDirection.y, -1, 1);
			ImGui::SliderFloat("Cone Z Direction:", &activePointLight.coneDirection.z, -1, 1);
			ImGui::SliderFloat("Attenuation:", &activePointLight.attenuation, 0, 2);

			scene.setPointLightAtIndex(activePointLight, i4);

			if (ImGui::Button("Add Point Light"))
			{
				scene.AddPointLight(activePointLight.position, activePointLight.color, activePointLight.coneDirection, activePointLight.attenuation, activePointLight.coneAngle);
				pointLightCounter++;
			}
			ImGui::SliderInt("Choose Point lLight", &i4, 1, pointLightCounter);







				
		}

		if (ImGui::CollapsingHeader("Blur & bloom"))
		{
			ImGui::SliderInt("Number of blurs", &i5, 0, 10);
			ImGui::Checkbox("Bloom", &bloom);
			scene.setBlurAndBloom(i5, bloom);
			ImGui::Checkbox("unifromMat", &unifromMat);
			scene.setunifromMat(unifromMat);

		
		}
		



		if (ImGui::Button("Reset"))
		{
			scaleX = 1;
			scaleY = 1;
			TranslateX = 0.2;
			TranslateY = 0.2;
			AroundX = 0;
			AroundY = 0;
			AroundZ = 0;
			TranslateXModel = 0;
			TranslateYModel = 0;
			AroundXModel = 0;
			AroundYModel = 0;
			AroundZModel = 0;
			normalsLength = 30;
			faceNormalsLength = 30;

			fovy =2.75;
			aspect = 1.0;
			Near = 1;
			Far = 150;

			left = -3.0;
			right = 3.0;
			bottom = -3.0;
			top = 3.0;
			Near2 = 0.1;
			Far2 = 200;

			 normalsLength = 5;
			 faceNormalsLength = 5;
		}














		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}






	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}

void cross(const glm::vec3& p1, const glm::vec3& p2) {
	glm::vec3 result;
	result[0] = p1[1] * p2[2] - p1[2] * p2[1];
	result[1] = p1[0] * p2[2] - p1[2] * p2[0];
	result[2] = p1[0] * p2[1] - p1[1] * p2[0];
}