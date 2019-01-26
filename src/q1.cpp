// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

#include "common.h"
#include "Mesh.h"
#include "FloorMeshFactory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "A1Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint projectionUniformLocation, modelUniformLocation, viewUniformLocation;

Mesh *defaultMesh, *customMesh, *floorMesh;

//----------------------------------------------------------------------------

// OpenGL initialization
void init() 
{
	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	// initializing input attributes
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vColor = glGetAttribLocation(program, "vColor");

	// initializing uniforms
	projectionUniformLocation = glGetUniformLocation(program, "projection");
	modelUniformLocation = glGetUniformLocation(program, "model");
	viewUniformLocation = glGetUniformLocation(program, "view");

	// vertices
	glm::vec4 vertices[] = {
		glm::vec4(-0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -2.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -2.5f, 1.0f),
		glm::vec4(-0.5f, -0.5f, -2.5f, 1.0f),
	};

	// colors
	glm::vec4 colors[] = {
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};

	defaultMesh = new Mesh();
	defaultMesh->init(vPosition, vColor);

	customMesh = new Mesh(vertices, colors, 6);
	customMesh->init(vPosition, vColor);

	floorMesh = FloorMeshFactory().createFloorMesh();
	floorMesh->init(vPosition, vColor);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//defaultMesh->display();

	//customMesh->display();

	floorMesh->display();

    glutSwapBuffers();
}

//----------------------------------------------------------------------------
GLfloat eyeX = 0.0f, eyeY = 0.0f, eyeZ = 0.0f;
GLfloat centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
void keyboard( unsigned char key, int x, int y )
{
    switch( key ) 
	{
		case 033: // Escape Key
		case 'q': case 'Q':
			exit( EXIT_SUCCESS );
			break;
		case 'w': case 'W':
			eyeZ -= 0.1f;
			break;
		case 's': case 'S':
			eyeZ += 0.1f;
			break;
		case 'd': case 'D':
			eyeX += 0.1f;
			break;
		case 'a': case 'A':
			eyeX -= 0.1f;
			break;
		case 't': case 'T':
			centerY += 0.1f;
			break;
		case 'g': case 'G':
			centerY -= 0.1f;
			break;
		case 'h': case 'H':
			centerX += 0.1f;
			break;
		case 'f': case 'F':
			centerX -= 0.1f;
			break;
    }
}

//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) 
	{
		return;
	}

	return;
}

//----------------------------------------------------------------------------

void update( void )
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(eyeX, 0.0f, eyeZ), glm::vec3(centerX, centerY, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}