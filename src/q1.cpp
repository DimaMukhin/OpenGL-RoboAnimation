// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

#include "common.h"
#include "Mesh.h"
#include "FloorMeshFactory.h"
#include "Robot.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *WINDOW_TITLE = "A1Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

GLuint projectionUniformLocation, modelUniformLocation, viewUniformLocation;

Mesh *floorMesh;

Robot *robot;

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

	floorMesh = FloorMeshFactory().createFloorMesh();
	floorMesh->init(vPosition, vColor);

	robot = new Robot(modelUniformLocation);
	robot->init(vPosition, vColor);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//customMesh->display();

	robot->display();

	floorMesh->display();

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
    switch( key ) 
	{
		case 033: // Escape Key
		case 'q': case 'Q':
			exit( EXIT_SUCCESS );
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
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 2.5f, 0.0f), glm::vec3(0.0f, 2.5f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));
}

//----------------------------------------------------------------------------

void reshape( int width, int height )
{
	GLfloat aspect = GLfloat(width) / height;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.5f, 100.0f);
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
}