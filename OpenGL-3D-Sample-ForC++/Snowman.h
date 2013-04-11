//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
// File: Snowman.h - Snowman definitions
//----------------------------------------------------------------------
#ifndef SNOWMAN_H
#define SNOWMAN_H

#include "OpenGL-3D-Sample-ForC++\type.h"

//----------------------------------------------------------------------
// Snowman
// A snowman is a rather uninteresting object. It just sits at some
// (x,y) position on the ground, and has the capability of being drawn.
//----------------------------------------------------------------------

class Snowman {
private:
	float x, y;	// location
public:
	Snowman(float xx = 0, float yy = 0); // constructor
	void draw(); // draw him
};

#endif
