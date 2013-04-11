//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           utilities.cpp
//  Description:    Some utility math functions
//  Programmer:     Dave Mount
//  For:            CMSC 425 - Spring 2013
//-----------------------------------------------------------------------

#include <ctime>						// time of day (for random seed)

#include "Utilities.h"
#include "Vector3d.h"					// for geometric constants

using namespace std;					// make std:: accessible

// ---------------------------------------------------------------  
// Utility functions for random number generation
// ---------------------------------------------------------------

void setSeed(int seed)					// set random seed
{
	if (seed == 0) srand(time(NULL));
	else srand(seed);
}

double unifDouble(double low, double high)
    { return low + (high-low)*double(rand())/double(RAND_MAX); }

int unifInt(int low, int high)
    { return int(unifDouble(low, high+1)); }

bool unifBool()
    { return unifDouble(0, 1) < 0.5; }    // this is true 50% of the time

// ---------------------------------------------------------------  
// Convertion to/from radians and degrees
// ---------------------------------------------------------------
double deg2rad(double deg)
	{ return deg* (Geom::PI/180.0); }

double rad2deg(double rad)
	{ return rad* 180.0/Geom::PI ; }

// ---------------------------------------------------------------  
// Clamps val to between min and max
// ---------------------------------------------------------------

double clamp(double val, double min, double max)
{
	if(max < Geom::GEOM_INF && val > max) val = max;
	else if(val < min) val = min;
	return val;
}

//----------------------------------------------------------------------
//  checkGLerror - OpenGL error handler
//----------------------------------------------------------------------

//void checkGLerror(const string& checkPoint) {
//	GLenum errCode;
//	while ((errCode = glGetError()) != GL_NO_ERROR) {
//		cerr << "OpenGL Error at "  << checkPoint  << ": "  << gluErrorString(errCode)  << endl;
//	}
//	cerr.flush();
//}

void checkGLerror(const string& checkPoint)
{
    GLenum errCode = glGetError();
	if (errCode == GL_NO_ERROR)  return;

    cerr << "OpenGL error detected: At checkpoint " << checkPoint << endl;
    while (errCode != GL_NO_ERROR) {
        cerr << "    ";
        switch (errCode) {
            case GL_INVALID_ENUM:
                cerr << "Invalid enumerated type as argument." << endl;
                break;
            case GL_INVALID_VALUE:
                cerr << "Argument out of range." << endl;
                break;
            case GL_INVALID_OPERATION:
                cerr << "Invalid operation for current state." << endl;
                break;
            case GL_STACK_OVERFLOW:
                cerr << "Stack overflow." << endl;
                break;
            case GL_STACK_UNDERFLOW:
                cerr << "Stack unverflow." << endl;
                break;
            case GL_OUT_OF_MEMORY:
                cerr << "Out of memory." << endl;
                break;
            default:
                cerr << "Unknown error code: " << errCode << endl;
                break;
        }
        errCode = glGetError();
    }
    cerr.flush();                       // make sure that output appears
}

//----------------------------------------------------------------------
//  error - called if an error occurs
//----------------------------------------------------------------------

void error(const string& msg, bool fatal)
{
    if (fatal) {
        cerr << "Error: " << msg << endl;
        exit(1);
    }
    else  cerr << "Warning: " << msg << endl;
}

//-----------------------------------------------------------------------
//	Get elapsed time in seconds since last call
//-----------------------------------------------------------------------
double getTimeStep()
{
	const int MILSEC_PER_SEC = 1000;	// milliseconds per second
	static bool firstTime = true;		// first time called
	static int previous = 0;					// previous time when called

	if (firstTime) {					// first time called?
		previous = glutGet(GLUT_ELAPSED_TIME);
		firstTime = false;
		return 0;
	}
	else {								// called earlier
		int current = glutGet(GLUT_ELAPSED_TIME);
		double elapsed = double(current - previous)/MILSEC_PER_SEC;
		cout << "prev = " << previous << " curr = " << current << " elapsed = " << elapsed << endl;
		previous = current;
		return elapsed;
	}
}
