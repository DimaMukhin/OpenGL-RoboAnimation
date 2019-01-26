#include "Mesh.h"

Mesh::Mesh()
{
}

void Mesh::init(glm::vec4 *vertices, glm::vec4 *colors, unsigned int numOfVertices, GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	this->numOfVertices = numOfVertices;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices + sizeof(colors[0]) * numOfVertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0]) * numOfVertices, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, sizeof(colors[0]) * numOfVertices, colors);

	// attributing vertices to shader
	glEnableVertexAttribArray(positionAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// attributing colors to shader
	glEnableVertexAttribArray(colorAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices[0]) * numOfVertices));

	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::display()
{
	// bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::update()
{
}

Mesh::~Mesh()
{
}
