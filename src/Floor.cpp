#include "Floor.h"

Floor::Floor(GLuint modelUniformLocation)
{
	this->modelUniformLocation = modelUniformLocation;

	GLuint numOfVertices = 4;

	glm::vec4 *vertices = new glm::vec4[numOfVertices] {
		glm::vec4(-2.5f, 0.0f, 2.5f, 1.0f),
		glm::vec4(2.5f, 0.0f, 2.5f, 1.0f),
		glm::vec4(2.5f, 0.0f, -2.5f, 1.0f),
		glm::vec4(-2.5f, 0.0f, -2.5f, 1.0f),
	};

	glm::vec4 *blackColors = new glm::vec4[numOfVertices] {
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	};

	glm::vec4 *grayColors = new glm::vec4[numOfVertices] {
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
	};

	const GLuint numOfIndices = 6;

	GLuint *indices = new GLuint[numOfIndices] {
		0, 1, 2, 2, 3, 0
	};

	blackTile = new Mesh2(vertices, blackColors, numOfVertices, indices, numOfIndices);
	grayTile = new Mesh2(vertices, grayColors, numOfVertices, indices, numOfIndices);
}

// initialize the floor
void Floor::init(GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	blackTile->init(positionAttribLocation, colorAttribLocation);
	grayTile->init(positionAttribLocation, colorAttribLocation);
}

// fisplay the floor
void Floor::display()
{
	int count = 0;
	Mesh2* currTile = grayTile;

	for (GLfloat x = -50; x < 55; x += 5.0f)
	{
		for (GLfloat z = 50; z > -55; z -= 5.0f)
		{
			glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(x, 0.0f, z));
			glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

			currTile->display();

			glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

			count++;

			if (count % 2 == 0)
			{
				currTile = grayTile;
			}
			else
			{
				currTile = blackTile;
			}
		}
	}
	
}

// delete the floor
Floor::~Floor()
{
}
