#pragma once

#include "common.h"
#include "Mesh2.h"

#include <glm/gtc/type_ptr.hpp>

class Floor
{
public:
	Floor(GLuint modelUniformLocation);

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	~Floor();

private:
	GLuint modelUniformLocation;

	Mesh2* blackTile;
	Mesh2* grayTile;
};