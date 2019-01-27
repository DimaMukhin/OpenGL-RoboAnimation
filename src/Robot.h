#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#include "Mesh.h"

class Robot
{
public:
	static glm::vec4* generateColors(int *colors, int numOfColors);

	static glm::vec4* generateVertices(int *vertices, int numOfVertices);

	static Mesh* createLimbMesh();

	static Mesh* createBodyMesh();

	static Mesh* createHeadMesh();

	Robot(GLuint modelUniformLocation);

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	~Robot();

private:
	static glm::vec4 *vertices;
	static glm::vec4 *colors;

	GLuint modelUniformLocation;

	GLfloat robotX, robotY, robotZ;
	GLfloat leftArmAngle, leftArmRotationSpeed, rightArmAngle, rightArmRotationSpeed;
	GLfloat leftLegAngle, leftLegRotationSpeed, rightLegAngle, rightLegRotationSpeed;

	Mesh *body;
	Mesh *leftLeg;
	Mesh *rightLeg;
	Mesh *leftFoot;
	Mesh *rightFoot;
	Mesh *leftArm;
	Mesh *rightArm;
	Mesh *leftHand;
	Mesh *rightHand;
	Mesh *head;

	void update();
};
