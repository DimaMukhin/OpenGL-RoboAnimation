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

Mesh *customMesh, *floorMesh;

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
		// body

		// body front
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c
		// body back
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d'
		// body right facing
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c'
		// body left facing
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d
		// body top
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // c
		// body bottom
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // a

		// left leg

		// left leg front
		glm::vec4(-1.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // c
		// left leg back
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // d'
		// left leg right facing
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // c'
		// left leg left facing
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // d
		// left leg top
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, -1.0f, 0.5f, 1.0f), // c
		// left leg bottom
		glm::vec4(-1.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, -3.0f, 0.5f, 1.0f), // a

		// right leg

		// right leg front
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(1.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(1.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // c
		// right leg back
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // d'
		// right leg right facing
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // c'
		// right leg left facing
		glm::vec4(1.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // d
		// right leg top
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // c
		glm::vec4(1.0f, -1.0f, 0.5f, 1.0f), // d
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, -1.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -1.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -1.0f, 0.5f, 1.0f), // c
		// right leg bottom
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // a
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, 0.5f, 1.0f), // b
		glm::vec4(0.0f, -3.0f, 0.5f, 1.0f), // a

		// left arm

		// left arm front
		glm::vec4(-2.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(-1.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(-2.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(-1.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(-2.0f, 2.0f, 0.5f, 1.0f), // c
		// left arm back
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-2.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-2.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // d'
		// left arm right facing
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-2.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(-2.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-2.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(-2.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(-2.0f, 2.0f, -0.5f, 1.0f), // c'
		// left arm left facing
		glm::vec4(-1.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // d
		// left arm top
		glm::vec4(-2.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(-1.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(-2.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-2.0f, 2.0f, 0.5f, 1.0f), // c
		// left arm bottom
		glm::vec4(-2.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(-2.0f, 0.0f, 0.5f, 1.0f), // a

		// right arm

		// right arm front
		glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(2.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(2.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(2.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // c
		// right arm back
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(2.0f, 2.0f, -0.5f, 1.0f), // d'
		// right arm right facing
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // c'
		// right arm left facing
		glm::vec4(2.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(2.0f, 2.0f, 0.5f, 1.0f), // d
		// right arm top
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(2.0f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(2.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(2.0f, 2.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, 2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, 2.0f, 0.5f, 1.0f), // c
		// right arm bottom
		glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), // a
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, 0.5f, 1.0f), // b
		glm::vec4(1.0f, 0.0f, 0.5f, 1.0f), // a

		// left foot

		// left foot front
		glm::vec4(-1.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(-1.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(-1.0f, -2.0f, 1.5f, 1.0f), // c
		// left foot back
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // d'
		// left foot right facing
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(-1.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(-1.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(-1.0f, -2.0f, -0.5f, 1.0f), // c'
		// left foot left facing
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // d
		// left foot top
		glm::vec4(-1.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, -2.0f, 1.5f, 1.0f), // c
		// left foot bottom
		glm::vec4(-1.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(-1.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(-1.0f, -3.0f, 1.5f, 1.0f), // a

		// right foot

		// right foot front
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(1.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(1.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(1.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // c
		// right foot back
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, -2.0f, -0.5f, 1.0f), // d'
		// right foot right facing
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // c'
		// right foot left facing
		glm::vec4(1.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, -2.0f, 1.5f, 1.0f), // d
		// right foot top
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // c
		glm::vec4(1.0f, -2.0f, 1.5f, 1.0f), // d
		glm::vec4(1.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, -2.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.0f, -2.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.0f, -2.0f, 1.5f, 1.0f), // c
		// right foot bottom
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // a
		glm::vec4(0.0f, -3.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, -3.0f, 1.5f, 1.0f), // b
		glm::vec4(0.0f, -3.0f, 1.5f, 1.0f), // a

		// left hand

		// left hand front
		glm::vec4(-2.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(-1.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(-2.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(-1.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(-1.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(-2.0f, 1.0f, 1.5f, 1.0f), // c
		// left hand back
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-2.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-2.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-1.0f, 1.0f, -0.5f, 1.0f), // d'
		// left hand right facing
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-2.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(-2.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-2.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(-2.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(-2.0f, 1.0f, -0.5f, 1.0f), // c'
		// left hand left facing
		glm::vec4(-1.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, 1.0f, 1.5f, 1.0f), // d
		// left hand top
		glm::vec4(-2.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(-1.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(-1.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(-1.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(-2.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(-2.0f, 1.0f, 1.5f, 1.0f), // c
		// left hand bottom
		glm::vec4(-2.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(-2.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(-1.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(-2.0f, 0.0f, 1.5f, 1.0f), // a

		// right hand

		// right hand front
		glm::vec4(1.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(2.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(1.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(2.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(2.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(1.0f, 1.0f, 1.5f, 1.0f), // c
		// right hand back
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(1.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(2.0f, 1.0f, -0.5f, 1.0f), // d'
		// right hand right facing
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(1.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(1.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(1.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(1.0f, 1.0f, -0.5f, 1.0f), // c'
		// right hand left facing
		glm::vec4(2.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(2.0f, 1.0f, 1.5f, 1.0f), // d
		// right hand top
		glm::vec4(1.0f, 1.0f, 1.5f, 1.0f), // c
		glm::vec4(2.0f, 1.0f, 1.5f, 1.0f), // d
		glm::vec4(2.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(2.0f, 1.0f, -0.5f, 1.0f), // d'
		glm::vec4(1.0f, 1.0f, -0.5f, 1.0f), // c'
		glm::vec4(1.0f, 1.0f, 1.5f, 1.0f), // c
		// right hand bottom
		glm::vec4(1.0f, 0.0f, 1.5f, 1.0f), // a
		glm::vec4(1.0f, 0.0f, -0.5f, 1.0f), // a'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, -0.5f, 1.0f), // b'
		glm::vec4(2.0f, 0.0f, 1.5f, 1.0f), // b
		glm::vec4(1.0f, 0.0f, 1.5f, 1.0f), // a

		// head hand

		// head front
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // a
		glm::vec4(0.5f, 2.0f, 0.5f, 1.0f), // b
		glm::vec4(-0.5f, 3.0f, 0.5f, 1.0f), // c
		glm::vec4(0.5f, 2.0f, 0.5f, 1.0f), // b
		glm::vec4(0.5f, 3.0f, 0.5f, 1.0f), // d
		glm::vec4(-0.5f, 3.0f, 0.5f, 1.0f), // c
		// head back
		glm::vec4(-0.5f, 2.0f, -0.5f, 1.0f), // a'
		glm::vec4(-0.5f, 3.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(-0.5f, 3.0f, -0.5f, 1.0f), // c'
		glm::vec4(0.5f, 3.0f, -0.5f, 1.0f), // d'
		// head right facing
		glm::vec4(-0.5f, 2.0f, -0.5f, 1.0f), // a'
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // a
		glm::vec4(-0.5f, 3.0f, -0.5f, 1.0f), // c'
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // a
		glm::vec4(-0.5f, 3.0f, 0.5f, 1.0f), // c
		glm::vec4(-0.5f, 3.0f, -0.5f, 1.0f), // c'
		// head left facing
		glm::vec4(0.5f, 2.0f, 0.5f, 1.0f), // b
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.5f, 3.0f, 0.5f, 1.0f), // d
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.5f, 3.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.5f, 3.0f, 0.5f, 1.0f), // d
		// head top
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // c
		glm::vec4(0.5f, 2.0f, 0.5f, 1.0f), // d
		glm::vec4(0.5f, 3.0f, -0.5f, 1.0f), // d'
		glm::vec4(0.5f, 3.0f, -0.5f, 1.0f), // d'
		glm::vec4(-0.5f, 3.0f, -0.5f, 1.0f), // c'
		glm::vec4(-0.5f, 3.0f, 0.5f, 1.0f), // c
		// head bottom
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // a
		glm::vec4(-0.5f, 2.0f, -0.5f, 1.0f), // a'
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.5f, 2.0f, -0.5f, 1.0f), // b'
		glm::vec4(0.5f, 2.0f, 0.5f, 1.0f), // b
		glm::vec4(-0.5f, 2.0f, 0.5f, 1.0f), // a
	};

	// colors
	glm::vec4 colors[] = {
		// body

		// body front
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		// body back
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// body right facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// body left facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// body top
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// body bottom
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),

		// left leg

		// left leg front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// left leg back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// left leg right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// left leg left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// left leg top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// left leg bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// right leg

		// right leg front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// right leg back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// right leg right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// right leg left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// right leg top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// right leg bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// left arm

		// left arm front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// left arm back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// left arm right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// left arm left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// left arm top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// left arm bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// right arm

		// right arm front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// right arm back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// right arm right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// right arm left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// right arm top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// right arm bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// left foot

		// left foot front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// left foot back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// left foot right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// left foot left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// left foot top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// left foot bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// right foot

		// right foot front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// right foot back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// right foot right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// right foot left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// right foot top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// right foot bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// left hand

		// left hand front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// left hand back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// left hand right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// left hand left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// left hand top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// left hand bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// right hand

		// right hand front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// right hand back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// right hand right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// right hand left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// right hand top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// right hand bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),

		// head

		// head front
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.8f, 1.0f),
		// head back
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		glm::vec4(0.0f, 0.9f, 0.4f, 1.0f),
		// head right facing
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.4f, 0.9f, 0.0f, 1.0f),
		// head left facing
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		glm::vec4(0.8f, 0.9f, 0.0f, 1.0f),
		// head top
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.9f, 0.5f, 0.0f, 1.0f),
		// head bottom
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.8f, 0.3f, 1.0f, 1.0f),
	};

	customMesh = new Mesh(vertices, colors, 36 * 10);
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

	customMesh->display();

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
GLfloat angle = 0.0f;
void update( void )
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	angle += 0.5f;
	if (angle > 360.0f) angle = 0.0f;

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