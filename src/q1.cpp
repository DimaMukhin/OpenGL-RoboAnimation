// Based on: http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/CHAPTER03/WINDOWS_VERSIONS/example2.cpp
// Modified to isolate the main program and use GLM

#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const char *WINDOW_TITLE = "A1Q1";
const double FRAME_RATE_MS = 1000.0/60.0;

//----------------------------------------------------------------------------

// OpenGL initialization
void init()
{
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader1.glsl", "fshader1.glsl" );
    glUseProgram( program );

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0, 0.0, 0.0, 0.0 ); 
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
       case 033: // Escape Key
       case 'q': case 'Q':
	       exit( EXIT_SUCCESS );
          break;
    }
}

//----------------------------------------------------------------------------

void
mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
	}
}

//----------------------------------------------------------------------------

void
update( void )
{
	// tick
}

//----------------------------------------------------------------------------

void
reshape( int width, int height )
{
}