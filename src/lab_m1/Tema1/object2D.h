#pragma once
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateHexagon(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangular(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateProiectil(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateInamic(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
}
