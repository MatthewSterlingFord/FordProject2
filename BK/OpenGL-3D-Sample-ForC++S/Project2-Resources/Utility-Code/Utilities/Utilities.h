//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           utilities.h
//  Description:    Some utility math functions
//  Programmer:     Dave Mount
//  For:            CMSC 425 - Spring 2013
//-----------------------------------------------------------------------

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>						// math definitions
#include <string>						// C++ strings
#include <iostream>						// C++ I/O
#include <sys/timeb.h>					// for timer
#include <GL/glut.h>					// OpenGL

#include "Vector3d.h"					// provides Geom::PI

// ---------------------------------------------------------------  
// Utility functions for random number generation
// ---------------------------------------------------------------

void setSeed(int seed = 0);				// set random seed
double unifDouble(double low, double high); // uniform double in [low,high]
int unifInt(int low, int high);			// uniform int in [low,high]
bool unifBool();						// random boolean

// ---------------------------------------------------------------  
// Clamps val to a value between min and max
// ---------------------------------------------------------------
double clamp(double val, double min, double max);

// ---------------------------------------------------------------  
// Convertion to/from radians and degrees
// ---------------------------------------------------------------
double deg2rad(double deg);
double rad2deg(double rad);

//----------------------------------------------------------------------
//  checkGLerror - OpenGL error handler
//      OpenGL does not generate error messages or exceptions.  In order
//      to check for errors, insert this call at strategic points within
//      the program.  The checkPoint argument is a label for where the
//      error checking was invoked from. Example:
//
//              checkGLerror("After texture-map setup")
//----------------------------------------------------------------------
void checkGLerror(const std::string& checkPoint);

//----------------------------------------------------------------------
//  error - error handler
//----------------------------------------------------------------------
void error(const std::string& msg, bool fatal);

//----------------------------------------------------------------------
//  get elapsed time in seconds
//----------------------------------------------------------------------
double getTimeStep();

#endif
