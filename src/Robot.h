#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#include "Mesh2.h"
#include "icosphere.h"

class Robot
{
public:
	static Mesh2* createLimbMesh();

	static Mesh2* createBodyMesh();

	static Mesh2* createHeadMesh();

	static Mesh2* createHandFootMesh();

	Robot(GLuint modelUniformLocation);

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	~Robot();

private:
	static GLuint bodyNumOfVertices;
	static glm::vec4 *bodyVertices;
	static glm::vec4 *bodyColors;
	static GLuint bodyNumOfIndices;
	static GLuint *bodyIndices;

	static GLuint limbNumOfVertices;
	static glm::vec4 *limbVertices;
	static glm::vec4 *limbColors;
	static GLuint limbNumOfIndices;
	static GLuint *limbIndices;

	static GLuint handFootNumOfVertices;
	static glm::vec4 *handFootVertices;
	static glm::vec4 *handFootColors;
	static GLuint handFootNumOfIndices;
	static GLuint *handFootIndices;

	GLuint modelUniformLocation;

	GLfloat robotX, robotY, robotZ;
	GLfloat leftArmAngle, leftArmRotationSpeed, rightArmAngle, rightArmRotationSpeed;
	GLfloat leftLegAngle, leftLegRotationSpeed, rightLegAngle, rightLegRotationSpeed;
	GLfloat handFootAngle, handFootRotationSpeed;

	Mesh2 *body;
	Mesh2 *limb;
	Mesh2 *head;
	Mesh2 *handFoot;

	void update();
};
