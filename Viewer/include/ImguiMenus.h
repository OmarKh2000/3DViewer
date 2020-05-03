#pragma once
#include <imgui/imgui.h>
#include "Scene.h"

void DrawImguiMenus(ImGuiIO& io, Scene& scene);
const glm::vec4& GetClearColor();
