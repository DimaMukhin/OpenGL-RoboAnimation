#include "FloorMeshFactory.h"

FloorMeshFactory::FloorMeshFactory()
{
}

Mesh* FloorMeshFactory::createFloorMesh()
{
	glm::vec4 *vertices = new glm::vec4[21*21*6];
	glm::vec4 *colors = new glm::vec4[21*21*6];
	
	glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 currColor = blue;

	int i = 0;
	int j = 0;
	int count = 0;

	for (GLfloat x = -50; x < 55; x += 5.0f) 
	{
		for (GLfloat z = 50; z > -55; z -= 5.0f)
		{
			 vertices[i++] = glm::vec4(x, 0.0f, z, 1.0f);
			 vertices[i++] = glm::vec4(x + 5, 0.0f, z, 1.0f);
			 vertices[i++] = glm::vec4(x + 5, 0.0f, z - 5, 1.0f);
			 vertices[i++] = glm::vec4(x, 0.0f, z, 1.0f);
			 vertices[i++] = glm::vec4(x + 5, 0.0f, z - 5, 1.0f);
			 vertices[i++] = glm::vec4(x, 0.0f, z - 5, 1.0f);

			colors[j++] = currColor;
			colors[j++] = currColor;
			colors[j++] = currColor;
			colors[j++] = currColor;
			colors[j++] = currColor;
			colors[j++] = currColor;

			count++;

			if (count % 2 == 0)
			{
				currColor = blue;
			}
			else
			{
				currColor = red;
			}
		}
	}

	return new Mesh(vertices, colors, 21*21*6);
}

FloorMeshFactory::~FloorMeshFactory()
{
}
