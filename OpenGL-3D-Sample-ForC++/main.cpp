//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: OpenGL-3D-Sample.cpp - Sample 3D OpenGL/GLUT program
//	Author: Dave Mount (adapted from a demo on Lighthouse3D)
//	For: CMSC 425
//
//	This is a sample program that illustrates OpenGL and GLUT. It
//	renders a picture of 36 snowmen. The camera can be moved by dragging
//	the mouse. The camera moves forward by hitting the up-arrow key and
//	back by moving the down-arrow key. Hit ESC or 'q' to exit.
//
//	Warning #1: This program uses the function glutSpecialUpFunc, which
//	may not be available in all GLUT implementations. If your system
//	does not have it, you can comment this line out, but the up arrow
//	processing will not be correct.
//
//	Warning #2: This is a minimalist program. Very little attention has
//	been paid to good programming technique.
//----------------------------------------------------------------------

#include <cstdlib> // C++ standard definitions
#include <iostream> // I/O stream

// include files are in a slightly different location for MacOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "World.h" // world object definitions
#include "Snowman.h"
#include "OpenGL-3D-Sample-ForC++\imageloader.h"

//----------------------------------------------------------------------
// Global variables
//----------------------------------------------------------------------

World theWorld; // the world


//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels.
//----------------------------------------------------------------------
void changeSize(int w, int h) 
{
	theWorld.setAspectRatio(float(w)/float(h)); // set new aspect ratio
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window 
}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update() 
{
	theWorld.camera -> update(theWorld.character -> char_direc_angle_about_Z, theWorld.cameraMode); // update the World
	theWorld.character -> update((theWorld.camera ->deltaMoveX + theWorld.camera ->deltaMoveY), 500 * (theWorld.camera -> deltaMoveX + theWorld.camera -> deltaMoveY + theWorld.camera -> deltaMoveZ));
	glutPostRedisplay(); // redraw everything (since camera may move)
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We clear the buffers using light blue (so the sky is already drawn)
// and then draw the world.
//----------------------------------------------------------------------
void draw() 
{
	glClearColor(0.0, 0.7, 1.0, 1.0); // sets the clear OR background (sky) color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glLoadIdentity(); // reset modelview transformation

	theWorld.draw(); // draw the world

	glutSwapBuffers(); // make it all visible
} 

//This is from http://www.videotutorialsrock.com/opengl_tutorial/cube/video.php
//Makes the image into a texture, and returns the id of the texture 
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 image->pixels);               //The actual pixel data
	return textureId;
}

//----------------------------------------------------------------------
// User-input callbacks
//
// C++ does not allow callbacks to be made to class methods, so 
// these are just redirections to the corresponding World handler.
//----------------------------------------------------------------------
void processNormalKeys(unsigned char key, int xx, int yy) { theWorld.processNormalKeys(key, xx, yy); }
void pressSpecialKey(int key, int xx, int yy) { theWorld.pressSpecialKey(key, xx, yy); }
void releaseSpecialKey(int key, int xx, int yy)  { theWorld.releaseSpecialKey(key, xx, yy); }
void mouseMove(int xx, int yy)  { theWorld.mouseMove(xx, yy); }
void mouseButton(int button, int state, int xx, int yy)  { theWorld.mouseButton(button, state, xx, yy); }


void initAllRendering() {
	glEnable(GL_DEPTH_TEST); // Check if obscured by anything already drawn if so dont drawn
	glEnable(GL_LIGHTING); // Now can use lighting 
	glEnable(GL_LIGHT0); // Draw everything with lighting 
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	const char* imagePath = "../grass24.bmp"; 
	Image* image = loadBMP(imagePath);
	theWorld.ground_texture_id = loadTexture(image);
	delete image;

	const char* imagePath2 = "../Project2-Resources\\Windows-Executable\\skybox-clouds.bmp"; 
	Image* image2 = loadBMP(imagePath2);
	theWorld.sky_texture_id = loadTexture(image2);
	delete image2;
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char **argv) 
{
	std::cout << "\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Drag mouse left-right to rotate camera\n\
  - Hold up-arrow/down-arrow to move camera forward/backward\n\
  - q or ESC to quit\n\
-----------------------------------------------------------------------\n";

	// general initializations
	 //Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0); // ...reletive to the upper left corner of screen...100 down and 100 over from top left corner
	glutInitWindowSize(400, 400); //...sets the inital size of the window 
	
	glutCreateWindow("WalkMan!");//... sets title of the window

	initAllRendering();

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(draw); // (re)display callback
	glutIdleFunc(update); // incremental update 
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed``
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	//glEnable(GL_DEPTH_TEST); //Makes 3D drawing work when something is in front of something else

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}
