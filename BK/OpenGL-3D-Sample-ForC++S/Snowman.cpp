//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: Snowman.cpp - Methods for Snowman object
//----------------------------------------------------------------------

#include <cstdlib> // C++ standard definitions

// include files are in a slightly different location for MacOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "Snowman.h" // Snowman definitions


//----------------------------------------------------------------------
// Snowman::Snowman - initialize snowman location
//----------------------------------------------------------------------
Snowman::Snowman(float xx, float yy)
{
	x = xx; 
	y = yy;
}

//----------------------------------------------------------------------
// Snowman::draw - draw a single snowman (at the proper location)
//
// A snowman consists of a large body sphere and a smaller head sphere.
// The head sphere has two black eyes and an orange conical nose. To
// better create the impression they are sitting on the ground, we draw
// a fake shadow, consisting of a dark circle under each.
//
// We make extensive use of nested transformations. Everything is drawn
// relative to the origin. The snowman's eyes and nose are positioned
// relative to a head sphere centered at the origin. Then the head is
// translated into its final position. The body is drawn and translated
// into its final position.
//----------------------------------------------------------------------
void Snowman::draw() 
{
	glPushMatrix();
		glTranslatef(x, y, 0); // translate to snowman's location

		// Draw body (a 20x20 spherical mesh of radius 0.75 at height 0.75)
		glColor3fv(GRASS_GREEN_RGB); // set drawing color to white
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.75);
			//glutSolidSphere(0.75, 20, 20);
			glutSolidCone(0.75, 10, 20, 20); // draw cone
		glPopMatrix();

		// Draw the head (a sphere of radius 0.25 at height 1.75)
		glColor3fv(SHELL_BROWN);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0); // position head
			glScalef(1.0f,1.0f,10.0f);
			glutSolidSphere(0.25, 20, 20); // head sphere

			// Draw Eyes (two small black spheres)
			glColor3f(0.0, 0.0, 0.0); // eyes are black
			glPushMatrix();
				glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
				glPushMatrix();
					glTranslatef(-0.05, 0.0, 0.0);
					glutSolidSphere(0.05, 10, 10); // right eye
				glPopMatrix();
				glPushMatrix();
					glTranslatef(+0.05, 0.0, 0.0);
					glutSolidSphere(0.05, 10, 10); // left eye
				glPopMatrix();
			glPopMatrix();

			// Draw Nose (the nose is an orange cone)
			glColor3f(1.0, 0.5, 0.5); // nose is orange
			glPushMatrix();
				glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
				glutSolidCone(0.08, 0.5, 10, 2); // draw cone
			glPopMatrix();
		glPopMatrix();

		// Draw a faux shadow beneath snow man (dark green circle)
		glDisable(GL_LIGHTING);
		glColor3fv(BLACK_RGB);
		glPushMatrix();
			glTranslatef(0.2, 0.2, 0.001);	// translate to just above ground
			glScalef(1.0, 1.0, 0.0); // scale sphere into a flat pancake
			glutSolidSphere(0.75, 20, 20); // shadow same size as body
		glPopMatrix();
		glEnable(GL_LIGHTING);

	glPopMatrix();
}
