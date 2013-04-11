//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: World.h - Definitions for World object
//----------------------------------------------------------------------
#ifndef WORLD_H
#define WORLD_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "../OpenGL-3D-Sample-ForC++/OpenGL-3D-Sample-ForC++/Camera.h" // camera def

#include <list> // STL list
#include "Character.h" // Snowman definitions
#include "Snowman.h"

//----------------------------------------------------------------------
// World
//
// Our world is rather simple. It consists of a ground, a collection of
// snowmen, and a camera. We provide methods for constructing the world,
// for drawing the world, and updating the world. The update procedure
// involves moving the camera as long as the user is holding down either
// the up or down arrow keys.
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------
class World {

private: // private data 
	bool isDragging; // true when mouse is dragging
	int xDragStart, yDragStart; // records the x-coordinate when dragging starts
	std::list<Snowman> snowmen; // list of snowmen

private: // private utility functions
	//void setUpCamera(); // camera set-up utility
public: // public interface
	Camera* camera;
	Character* character;
	World(); // constructor
	GLuint ground_texture_id;
	GLuint sky_texture_id;
	int cameraMode;

	void setAspectRatio(float ratio); // set the aspect ratio
	void draw(); // draw everything
	void processNormalKeys(unsigned char key, int xx, int yy);
	void pressSpecialKey(int key, int xx, int yy); // special key press
	void releaseSpecialKey(int key, int xx, int yy); // special key release
	void mouseMove(int xx, int yy); // mouse dragged
	void mouseButton(int button, int state, int xx, int yy); // mouse button
};

#endif
