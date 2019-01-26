#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Mesh.h"

class FloorMeshFactory
{
public:
	FloorMeshFactory();

	Mesh* createFloorMesh();

	~FloorMeshFactory();
};

