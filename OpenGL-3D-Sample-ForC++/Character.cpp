//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: Snowman.cpp - Methods for Snowman object
//----------------------------------------------------------------------
#include <iostream>
//#include <stdlib.h> 
#include <cstdlib> // C++ standard definitions

// include files are in a slightly different location for MacOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Character.h" // Snowman definitions

//----------------------------------------------------------------------
// Snowman::Snowman - initialize snowman location
//----------------------------------------------------------------------
Character::Character()
{
	char_loc_x = 0.0; 
	char_loc_y = 0.0;
	char_loc_z = 0.0;

	char_dir_x = 0.0; 
	char_dir_y = 0.0;
	char_dir_z = 0.0;
	
	char_direc_angle_about_Z = 0.0;
	this -> alapedTime = 0.0;
	alapedWingTime = 0.0;
}

void Character::update(int isMovingXorY, float time){
	//if(alapedTime > M){
		
		if(char_loc_z < 2){
			alapedTime = alapedTime + time;	
		}
		

		if(char_loc_z > 1){
			alapedWingTime = alapedWingTime + 1000;
		}
		//}

	//}else{
		//alapedTime = alapedTime + time;
	//}
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
void Character::draw() 
{
	glPushMatrix();
	glTranslatef(char_loc_x, char_loc_y, char_loc_z); // translate character to its location
	glRotatef(char_direc_angle_about_Z, 0.0f, 0.0f, 1.0f); // rotates character to point movement direction
		glPushMatrix();
			  glTranslatef(0, 0, 0.25); // Raise turtle up to ground level 
			  glRotatef(-90, 0.0f, 0.0f, 1.0f);  // Rotate char 90 around the z-axis to start facing the right. SETS Thete to be ZERO/ init alongX-axiz
			  glRotatef(90, 1.0f, 0.0f, 0.0f);  // Rotate char 90 around the x-axis to puts turtle on all fours 
			  glRotatef(180, 0.0f, 1.0f, 0.0f); // Rotate char 180 around the y-axis to puts turtle on its head burred
												// Read from here: turtle starts on back two legs	
		    
			// Draw body (a 20x20 scaled spherical mesh of radius 0.75 at height 0.75)
			glColor3f(0.0, 1.0, 0.2); // set drawing color to white
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.75);
				glScalef(0.15f, 0.15f, 1.8f);
				glutSolidSphere(0.75, 20, 20);
			glPopMatrix();

			 // set drawing color to white
	/*		glPushMatrix();
				glTranslatef(0.0, 0.0, 0.75);
				glScalef(0.5f,0.5f,1.0f);
				//glRotatef(30, 1.0f, 1.0f, 0.0f);
				glutSolidSphere(0.75, 20, 20);
			glPopMatrix();
	*/	
			//Draw shell (Sphere)
			glColor3fv(SHELL_BROWN); // set drawing color to white
				glPushMatrix();
				glTranslatef(0.0, 0.25, 0.75);
				//glScalef(0.5f,0.5f,1.0f);
				glutSolidSphere(0.6, 20, 20);
			glPopMatrix();

			//Draw left LEGGG
		    //glColor3f(0.0, 0.9, 0.2);
			glColor3fv(GREEN_RGB); 
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedTime/1000.0));
					//ANAMATION END
					glTranslatef(0.5, -0.25, 0.5);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glRotatef(45.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();
			
			//Draw RIGHT LEGG
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedTime/1000.0));
					//ANAMATION END
					glTranslatef(-0.5, -0.25, 0.5);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();

			//Draw left ARRRM
	   		//glColor3fv(0.0, 0.5, 0.1); //  
				glColor3fv(GREEN_RGB); //
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedTime/1000.0));
					//ANAMATION END
					glTranslatef(0.5, -0.25, 1.25);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();

			//Draw RIGHT ARRM
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedTime/1000.0));
					//ANAMATION END
					glTranslatef(-0.5, -0.25, 1.25);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();

				//Draw left WING
	   		//glColor3fv(0.0, 0.5, 0.1); //  
				glColor3fv(RED_RGB); //
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedWingTime/1000.0));
					//ANAMATION END
					glTranslatef(0.5, 0.25, 1.25);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();

			//Draw RIGHT WING
				glPushMatrix();
					//ANAMATION START
					glTranslatef(0.0, 0.0, 0.1*sin(alapedWingTime/1000.0));
					//ANAMATION END
					glTranslatef(-0.5, 0.25, 1.25);	
					glScalef(1.5f,1.0f,1.0f);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidSphere(0.15, 20, 20);
				glPopMatrix();
			
			glColor3fv(GREEN_RGB); //
			//glColor3f(0.0, 0.5, 0.2); 
			// Draw the head (a sphere of radius 0.25 at height 1.75)
			glPushMatrix();
				glTranslatef(0.0, 0.0, 1.75); // position head
				glScalef(1.0f,1.0f,1.5f);
				glRotatef(90.0, -1.0, 0.0, 0.0); 
				glutSolidSphere(0.25, 20, 20); // head sphere

				// Draw Eyes (two small black spheres)
				glColor3fv(BLACK_RGB); // Black eyes dots 
				glPushMatrix();
					glTranslatef(0.0, -0.2, 0.10); // lift eyes to final position
					glPushMatrix();
						glTranslatef(-0.05, 0.0, 0.0);
						glutSolidSphere(0.05, 10, 10); // right eye
					glPopMatrix();
					glPushMatrix();
						glTranslatef(+0.05, 0.0, 0.0);
						glutSolidSphere(0.05, 10, 10); // left eye
					glPopMatrix();
				glPopMatrix();

				glColor3fv(WHITE_RGB); // White eyes balls
				glPushMatrix();
					glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
					glPushMatrix();
						glTranslatef(-0.05, 0.0, 0.0);
						glutSolidSphere(0.07, 10, 10); // right eye
					glPopMatrix();
					glPushMatrix();
						glTranslatef(+0.05, 0.0, 0.0);
						glutSolidSphere(0.07, 10, 10); // left eye
					glPopMatrix();
				glPopMatrix();

				// Draw Nose 
				// TODO Fix noise
				glColor3fv(GREEN_RGB); // nose is orange
				glPushMatrix();
					glTranslatef(0.0, -0.18, 0.10);
					glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
					//glutSolidCone(0.08, 0.5, 10, 2); // draw cone
					glutSolidCube(0.05); // draw cone
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		// Draw a faux shadow beneath snow man (dark green circle)
		//glDisable(GL_LIGHTING);
		//glColor3f(0.0, 0.1, 0.0);
		//glPushMatrix();
		//	glTranslatef(0.3, 0.2, 0.001);	// translate to just above ground
		//	glScalef(1.0, 1.0, 0.0); // scale sphere into a flat pancake
		//	glutSolidSphere(0.75, 20, 20); // shadow same size as body
		//glPopMatrix();
		//glEnable(GL_LIGHTING);
	glPopMatrix();
}
