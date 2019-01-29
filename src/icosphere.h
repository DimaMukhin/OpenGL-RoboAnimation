#pragma once

#include "common.h" // for OpenGL types
#include "Mesh.h"
#include <vector>
#include <glm/glm.hpp>

extern void icosphere(int sub, std::vector<glm::vec4> &vertices, std::vector<GLuint> &indices);

extern Mesh* createIcosphereMesh(glm::vec4 color);
