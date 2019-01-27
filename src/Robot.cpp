#include "Robot.h"

/*************** Static Block Start ***************/

glm::vec4* Robot::colors = new glm::vec4[8] {
	glm::vec4(0.0, 0.0, 0.0, 1.0),  // black
	glm::vec4(1.0, 0.0, 0.0, 1.0),  // red
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(0.0, 0.0, 1.0, 1.0),  // blue
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 1.0, 1.0, 1.0),  // white
	glm::vec4(0.0, 1.0, 1.0, 1.0)   // cyan
};

glm::vec4* Robot::vertices = new glm::vec4[24] {
	glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a body
	glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b body
	glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c body
	glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d body
	glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // a' body
	glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b' body
	glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c' body
	glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d' body

	glm::vec4(-0.5f, -2.0f, 0.5f, 1.0f), // a limb
	glm::vec4(0.5f, -2.0f, 0.5f, 1.0f), // b limb
	glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f), // c limb
	glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), // d limb
	glm::vec4(-0.5f, -2.0f, -0.5f, 1.0f), // a' limb
	glm::vec4(0.5f, -2.0f, -0.5f, 1.0f), // b' limb
	glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f), // c' limb
	glm::vec4(0.5f, 0.0f, -0.5f, 1.0f), // d' limb

	glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f), // a head
	glm::vec4(0.5f, -0.5f, 0.5f, 1.0f), // b head
	glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f), // c head
	glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), // d head
	glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // a' head
	glm::vec4(0.5f, -0.5f, -0.5f, 1.0f), // b' head
	glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f), // c' head
	glm::vec4(0.5f, 0.5f, -0.5f, 1.0f), // d' head

};

glm::vec4 * Robot::generateColors(int * colors, int numOfColors)
{
	glm::vec4 *generatedColors = new glm::vec4[numOfColors];

	for (int i = 0; i < numOfColors; i++)
	{

		generatedColors[i] = Robot::colors[colors[i]];
	}

	return generatedColors;
}

glm::vec4 * Robot::generateVertices(int * vertices, int numOfVertices)
{
	glm::vec4 *generatedVertices = new glm::vec4[numOfVertices];

	for (int i = 0; i < numOfVertices; i++)
	{

		generatedVertices[i] = Robot::vertices[vertices[i]];
	}

	return generatedVertices;
}

Mesh* Robot::createLimbMesh()
{
	GLfloat numOfVertices = 36;

	glm::vec4 *vertices;
	int vertexIndices[] = {
		8,9,10,9,11,10,
		12,14,13,13,14,15,
		12,8,14,8,10,14,
		9,13,11,13,15,11,
		10,11,15,15,14,10,
		8,12,13,13,9,8
	};
	vertices = Robot::generateVertices(vertexIndices, numOfVertices);

	glm::vec4 *colors;
	int colorIndices[] = {
		0,0,0,0,0,0,
		1,1,1,1,1,1,
		2,2,2,2,2,2,
		3,3,3,3,3,3,
		4,4,4,4,4,4,
		5,5,5,5,5,5
	};
	colors = Robot::generateColors(colorIndices, numOfVertices);

	return new Mesh(vertices, colors, numOfVertices);
}

Mesh* Robot::createBodyMesh()
{
	GLfloat numOfVertices = 36;

	glm::vec4 *vertices;
	int vertexIndices[] = {
		0,1,2,1,3,2,
		4,6,5,5,6,7,
		4,0,6,0,2,6,
		1,5,3,5,7,3,
		2,3,7,7,6,2,
		0,4,5,5,1,0
	};
	vertices = Robot::generateVertices(vertexIndices, numOfVertices);

	glm::vec4 *colors;
	int colorIndices[] = {
		0,0,0,0,0,0,
		1,1,1,1,1,1,
		2,2,2,2,2,2,
		3,3,3,3,3,3,
		4,4,4,4,4,4,
		5,5,5,5,5,5
	};
	colors = Robot::generateColors(colorIndices, numOfVertices);

	return new Mesh(vertices, colors, numOfVertices);
}

Mesh* Robot::createHeadMesh()
{
	GLfloat numOfVertices = 36;

	glm::vec4 *vertices;
	int vertexIndices[] = {
		16,17,18,17,19,18,
		20,22,21,21,22,23,
		20,16,22,16,18,22,
		17,21,19,21,23,19,
		18,19,23,23,22,18,
		16,20,21,21,17,16
	};
	vertices = Robot::generateVertices(vertexIndices, numOfVertices);

	glm::vec4 *colors;
	int colorIndices[] = {
		0,0,0,0,0,0,
		1,1,1,1,1,1,
		2,2,2,2,2,2,
		3,3,3,3,3,3,
		4,4,4,4,4,4,
		5,5,5,5,5,5
	};
	colors = Robot::generateColors(colorIndices, numOfVertices);

	return new Mesh(vertices, colors, numOfVertices);
}

/************************* Static Block End ************************/

Robot::Robot(GLuint modelUniformLocation)
{
	this->modelUniformLocation = modelUniformLocation;
	body = createBodyMesh();
	leftLeg = createLimbMesh();
	rightLeg = createLimbMesh();
	leftFoot = createLimbMesh();
	rightFoot = createLimbMesh();
	leftArm = createLimbMesh();
	rightArm = createLimbMesh();
	leftHand = createLimbMesh();
	rightHand = createLimbMesh();
	head = createHeadMesh();
}

void Robot::init(GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	body->init(positionAttribLocation, colorAttribLocation);
	leftLeg->init(positionAttribLocation, colorAttribLocation);
	rightLeg->init(positionAttribLocation, colorAttribLocation);
	leftFoot->init(positionAttribLocation, colorAttribLocation);
	rightFoot->init(positionAttribLocation, colorAttribLocation);
	leftArm->init(positionAttribLocation, colorAttribLocation);
	rightArm->init(positionAttribLocation, colorAttribLocation);
	leftHand->init(positionAttribLocation, colorAttribLocation);
	rightHand->init(positionAttribLocation, colorAttribLocation);
	head->init(positionAttribLocation, colorAttribLocation);
}

GLfloat angle = 0.0f;
void Robot::display()
{
	glm::mat4 model;
	std::stack<glm::mat4> s;
	
	// Robot transformations
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	// body
	body->display();

	// left leg
	s.push(model);
	model = glm::translate(model, glm::vec3(-0.5f, -1.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	leftLeg->display();
	model = s.top();
	s.pop();

	// right leg
	s.push(model);
	model = glm::translate(model, glm::vec3(0.5f, -1.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	rightLeg->display();
	model = s.top();
	s.pop();

	// left foot
	s.push(model);
	model = glm::translate(model, glm::vec3(-0.5f, -2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	leftFoot->display();
	model = s.top();
	s.pop();

	// right foot
	s.push(model);
	model = glm::translate(model, glm::vec3(0.5f, -2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	rightFoot->display();
	model = s.top();
	s.pop();

	// left arm
	s.push(model);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	leftArm->display();
	model = s.top();
	s.pop();

	// right arm
	s.push(model);
	model = glm::translate(model, glm::vec3(1.5f, 2.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	rightArm->display();
	model = s.top();
	s.pop();

	// left hand
	s.push(model);
	model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	leftArm->display();
	model = s.top();
	s.pop();

	// right hand
	s.push(model);
	model = glm::translate(model, glm::vec3(1.5f, 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	rightArm->display();
	model = s.top();
	s.pop();

	//head
	s.push(model);
	model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	head->display();
	model = s.top();
	s.pop();

	// reseting model uniform to not affect any other models/mesh
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	angle += 0.5f;
	if (angle > 360.0f) angle = 0.0f;
}

Robot::~Robot()
{
	delete body;
	delete leftLeg;
}
