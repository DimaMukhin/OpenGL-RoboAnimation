#pragma once

#include "common.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh2
{
public:
	Mesh2();

	Mesh2(glm::vec4 *vertices, glm::vec4 *colors, GLuint numOfVertices, GLuint *indices, GLuint numOfIndices);

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	void update();

	~Mesh2();

private:
	GLuint VAO, VBO, IBO;

	GLuint numOfVertices;
	glm::vec4 *vertices, *colors;

	GLuint numOfIndices;
	GLuint *indices;
};

