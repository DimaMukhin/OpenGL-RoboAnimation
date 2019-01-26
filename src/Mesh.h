#pragma once

#include "common.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh
{
public:
	Mesh();

	void init(glm::vec4 *vertices, glm::vec4 *colors, unsigned int numOfVertices, GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	void update();

	~Mesh();

private:
	GLuint VAO, VBO;
	GLuint numOfVertices;
};

