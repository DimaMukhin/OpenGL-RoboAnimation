#pragma once

#include "common.h" // for OpenGL types
#include "Mesh2.h"
#include <vector>
#include <glm/glm.hpp>

extern void icosphere(int sub, std::vector<glm::vec4> &vertices, std::vector<GLuint> &indices);

extern Mesh2* createIcosphereMesh(glm::vec4 color);
