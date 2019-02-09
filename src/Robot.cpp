#include "Robot.h"

/*************** Static Block Start ***************/

GLuint Robot::bodyNumOfVertices = 8;
glm::vec4* Robot::bodyVertices = new glm::vec4[Robot::bodyNumOfVertices] {
	glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a body
	glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b body
	glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c body
	glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d body
	glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // a' body
	glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b' body
	glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c' body
	glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d' body
};
glm::vec4* Robot::bodyColors = new glm::vec4[Robot::bodyNumOfIndices]{
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
	glm::vec4(0.0, 1.0, 1.0, 1.0),   // cyan
};

GLuint Robot::bodyNumOfIndices = 36;
GLuint* Robot::bodyIndices = new GLuint[Robot::bodyNumOfIndices] {
	0,1,2,1,3,2,
	4,6,5,5,6,7,
	4,0,6,0,2,6,
	1,5,3,5,7,3,
	2,3,7,7,6,2,
	0,4,5,5,1,0
};

GLuint Robot::limbNumOfVertices = 8;
glm::vec4* Robot::limbVertices = new glm::vec4[Robot::limbNumOfVertices]{
	glm::vec4(-0.5f, -2.0f, 0.5f, 1.0f), // a limb
	glm::vec4(0.5f, -2.0f, 0.5f, 1.0f), // b limb
	glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f), // c limb
	glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), // d limb
	glm::vec4(-0.5f, -2.0f, -0.5f, 1.0f), // a' limb
	glm::vec4(0.5f, -2.0f, -0.5f, 1.0f), // b' limb
	glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f), // c' limb
	glm::vec4(0.5f, 0.0f, -0.5f, 1.0f), // d' limb
};
glm::vec4* Robot::limbColors = new glm::vec4[Robot::limbNumOfIndices]{
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
	glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
};

GLuint Robot::limbNumOfIndices = 36;
GLuint* Robot::limbIndices = new GLuint[Robot::limbNumOfIndices]{
	0,1,2,1,3,2,
	4,6,5,5,6,7,
	4,0,6,0,2,6,
	1,5,3,5,7,3,
	2,3,7,7,6,2,
	0,4,5,5,1,0
};

GLuint Robot::handFootNumOfVertices = 5;
glm::vec4* Robot::handFootVertices = new glm::vec4[Robot::handFootNumOfVertices]{
	glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f), // a pyramid
	glm::vec4(0.5f, 0.0f, 0.5f, 1.0f), // b pyramid
	glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f), // a' pyramid
	glm::vec4(0.5f, 0.0f, -0.5f, 1.0f), // b' pyramid
	glm::vec4(0.0f, -2.0f, 0.0f, 1.0f), // pyramid point

};
glm::vec4* Robot::handFootColors = new glm::vec4[Robot::handFootNumOfIndices]{
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
	glm::vec4(1.0, 0.0, 0.0, 1.0),  // red
};

GLuint Robot::handFootNumOfIndices = 18;
GLuint* Robot::handFootIndices = new GLuint[Robot::handFootNumOfIndices]{
	0, 1, 4,
	1, 3, 4,
	3, 2, 4,
	2, 0, 4,
	0,1,3,3,2,0,
};

// create limb mesh (its a 3d rectangle shape)
Mesh2* Robot::createLimbMesh()
{
	return new Mesh2(Robot::limbVertices, Robot::limbColors, Robot::limbNumOfVertices, Robot::limbIndices, Robot::limbNumOfIndices);
}

// create body mesh (similar 3d rectangle shape but different)
Mesh2* Robot::createBodyMesh()
{
	return new Mesh2(Robot::bodyVertices, Robot::bodyColors, Robot::bodyNumOfVertices, Robot::bodyIndices, Robot::bodyNumOfIndices);
}

// create head mesh (sphere)
Mesh2* Robot::createHeadMesh()
{
	return createIcosphereMesh(glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
}

// create hand/foor mesh (pyramid)
Mesh2* Robot::createHandFootMesh()
{
	return new Mesh2(Robot::handFootVertices, Robot::handFootColors, Robot::handFootNumOfVertices, Robot::handFootIndices, Robot::handFootNumOfIndices);
}

/************************* Static Block End ************************/

Robot::Robot(GLuint modelUniformLocation)
{
	this->modelUniformLocation = modelUniformLocation;

	// robot starting position in world coord
	robotX = -10.0f;
	robotY = 3.0f;
	robotZ = -20.0f;

	// robot arm angle of rotation
	leftArmAngle = 0.0f;
	leftArmRotationSpeed = -0.8f;
	rightArmAngle = 0.0f;
	rightArmRotationSpeed = 0.8f;

	// robot leg angle of rotation
	leftLegAngle = 0.0f;
	leftLegRotationSpeed = 0.8f;
	rightLegAngle = -45.0f;
	rightLegRotationSpeed = -0.8f;

	// hand and foot rotation
	handFootAngle = 0.0f;
	handFootRotationSpeed = 5.0f;

	body = createBodyMesh();
	limb = createLimbMesh();
	head = createHeadMesh();
	handFoot = createHandFootMesh();
}

// initialize the robot
void Robot::init(GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	body->init(positionAttribLocation, colorAttribLocation);
	limb->init(positionAttribLocation, colorAttribLocation);
	head->init(positionAttribLocation, colorAttribLocation);
	handFoot->init(positionAttribLocation, colorAttribLocation);
}

// display the robot
void Robot::display()
{
	glm::mat4 model;
	std::stack<glm::mat4> s;
	
	// Robot transformations
	model = glm::translate(model, glm::vec3(robotX, robotY, robotZ));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	// body
	body->display();

	// left leg
	s.push(model);
	model = glm::translate(model, glm::vec3(-0.5f, -1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(leftLegAngle), glm::vec3(1.0f, 0.0f, 0.0f));

		// left foot
		s.push(model);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(handFootAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		handFoot->display();
		model = s.top();
		s.pop();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	limb->display();
	model = s.top();
	s.pop();

	// right leg
	s.push(model);
	model = glm::translate(model, glm::vec3(0.5f, -1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rightLegAngle), glm::vec3(1.0f, 0.0f, 0.0f));

		// right foot
		s.push(model);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(handFootAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		handFoot->display();
		model = s.top();
		s.pop();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	limb->display();
	model = s.top();
	s.pop();

	// left arm
	s.push(model);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(leftArmAngle), glm::vec3(1.0f, 0.0f, 0.0f));

		// left hand
		s.push(model);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(handFootAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		handFoot->display();
		model = s.top();
		s.pop();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	limb->display();
	model = s.top();
	s.pop();

	// right arm
	s.push(model);
	model = glm::translate(model, glm::vec3(1.5f, 2.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rightArmAngle), glm::vec3(1.0f, 0.0f, 0.0f));

		// right hand
		s.push(model);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(handFootAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		handFoot->display();
		model = s.top();
		s.pop();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	limb->display();
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

	update();
}

// delete the robot
Robot::~Robot()
{
}

/****************** private block ***********************/

// update the robot
void Robot::update()
{
	robotX += 0.1f;
	if (robotX > 10.0f)
	{
		robotX = -10.0f;
	}

	leftArmAngle += leftArmRotationSpeed;
	if (leftArmAngle > 45.0f)
	{
		leftArmRotationSpeed *= -1;
	}
	else if (leftArmAngle < -45.0f)
	{
		leftArmRotationSpeed *= -1;
	}

	rightArmAngle += rightArmRotationSpeed;
	if (rightArmAngle > 45.0f)
	{
		rightArmRotationSpeed *= -1;
	}
	else if (rightArmAngle < -45.0f)
	{
		rightArmRotationSpeed *= -1;
	}

	leftLegAngle += leftLegRotationSpeed;
	if (leftLegAngle > 10.0f)
	{
		leftLegRotationSpeed *= -1;
	}
	else if (leftLegAngle < -45.0f)
	{
		leftLegRotationSpeed *= -1;
	}

	rightLegAngle += rightLegRotationSpeed;
	if (rightLegAngle > 10.0f)
	{
		rightLegRotationSpeed *= -1;
	}
	else if (rightLegAngle < -45.0f)
	{
		rightLegRotationSpeed *= -1;
	}

	handFootAngle += handFootRotationSpeed;
	if (handFootAngle >= 360.0f)
	{
		handFootAngle = 0.0f;
	}
}
