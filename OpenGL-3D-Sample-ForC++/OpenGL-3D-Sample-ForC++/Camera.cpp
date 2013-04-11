// include files are in a slightly different location for MacOS
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>    // C++ I/O

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Camera.h"
#include "type.h"
#include "../Project2-Resources/Utility-Code/Vector3d/Vector3d.h"


using namespace std;                    // make std accessible

// Camera eye or position cart coords
float	behind_char_loc_x = 0.0; 
float	behind_eye_y = 0.0; 
float	behind_eye_z = 1.0;// initially 5 units south of origin

// Camera at or look direction cart coords 
float	behind_at_x = 0.0; 
float	behind_at_y = 0.0;
float	behind_at_z = 0.0;

// Camera up vector cart coords 
float	behind_up_x = 0.0; 
float	behind_up_y = 0.0;
float	behind_up_z = 0.0;

// Camera eye or position cart coords
float	first_char_loc_x = 0.0; 
float	first_eye_y = 0.0; 
float	first_eye_z = 1.0;// initially 5 units south of origin

// Camera at or look direction cart coords 
float	first_at_x = 0.0; 
float	first_at_y = 0.0;
float	first_at_z = 0.0;

// Camera up vector cart coords 
float	first_up_x = 0.0; 
float	first_up_y = 0.0;
float	first_up_z = 0.0;



// Places the camera at (x,y,1) pointing along (lx, ly, 0). The camera
// has a 45 degree vertical field of view. Its aspect ratio matches the
// graphics window. The near and far clipping planes are set to 1 and
// 100, respectively. (Anything closer or farther is not drawn.)
//----------------------------------------------------------------------

Camera::Camera(Character* param_character){
	focusCharacter = param_character;

	aspectRatio = 1; // default aspect ratio (will be changed)

// Camera eye or position cart coords
//	char_loc_x = 0.0; 
//	eye_y = 0.0; 
//	eye_z = 1.0;// initially 5 units south of origin
	
	// Camera at or look direction cart coords 
	at_x = 0.0; 
	at_y = 0.0;
	at_z = 0.0;
	
	// Camera up vector cart coords 
	up_x = 0.0; 
	up_y = 0.0;
	up_z = 0.0;

	deltaMoveX = 0.0; // initially camera doesn't move
	deltaMoveY = 0.0; // initially camera doesn't move
	deltaMoveZ = 0.0; // initially camera doesn't move

	angleAroundZ = 0.0; // angle of rotation for the camera direction
	angleAroundX = 0.0; // angle of rotation for the camera direction
	
	deltaDragX = 0.0; // additional angle change when dragging
	deltaDragY = 0.0;
	//Must be called based on mode.
	//setUpCamera();
}

float toRads(float degree){
	return (M_PI / 180.0) * degree;
}

void Camera::setUpCameraDefault(){
	gluLookAt(
		focusCharacter -> char_loc_x,  focusCharacter -> char_loc_y, focusCharacter -> char_loc_z,  
			at_x,   at_y,  at_z,		   
			up_x,   up_y,  up_z);		   

	//Switch to setting the camera perspective
	glMatrixMode(GL_PROJECTION); // projection matrix is activea
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    
	gluPerspective(45.0,                  //The camera angle
                   aspectRatio,           //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   100.0);                //The far z clipping coordinate

	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void Camera::setUpCameraAbove(float param_char_direc_angle_about_Z){
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	//updatedAboveParams(char_loc_x,  eye_y,  eye_z);
	
//ALWAYS STAY 25 Z DIRECTLY ABOVE the char
 	float temp_eye_x = focusCharacter->char_loc_x; 
	float temp_eye_y = focusCharacter->char_loc_y;		
	float temp_eye_z = focusCharacter->char_loc_z + 25.0; 
	
	// Camera at or look direction cart coords 
	float temp_at_x = focusCharacter->char_loc_x; 
	float temp_at_y = focusCharacter->char_loc_y;
	float temp_at_z = focusCharacter->char_loc_z;

	// Camera up vector cart coords 
	float temp_up_x = 0.0; 
	float temp_up_y = 1.0;
	float temp_up_z = 0.0;

	gluLookAt(
			temp_eye_x, temp_eye_y, temp_eye_z,  // eye/camera position... where is the camera. Starts 25 units above orgin/character. 
			temp_at_x, temp_at_y, temp_at_z,	   // looking direction/at vector... for above should always be at character
			temp_up_x, temp_up_y, temp_up_z		   // alines top of camera with the y-axiz so that y is up.
	);

	//Switch to setting the camera perspective
	glMatrixMode(GL_PROJECTION); // projection matrix is activea
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    
	gluPerspective(45.0,                  //The camera angle
                   aspectRatio,           //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   100.0);                //The far z clipping coordinate

	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

void Camera::setUpCameraBehind(float param_char_direc_angle_about_Z){
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	angleAroundZ = param_char_direc_angle_about_Z;
	
	// eye position... where is the camera. 
	    //this for eye position makes cool camera movements  
    	//10*x * cos(toRads(param_char_direc_angle_about_Z)),  10*y * sin(toRads(param_char_direc_angle_about_Z)), 10.0,  // eye position... where is the camera. First person camera should be head 
	float temp_eye_x = focusCharacter->char_loc_x - 10 * cosf(toRads(param_char_direc_angle_about_Z));  
	float temp_eye_y = focusCharacter->char_loc_y - 10 * sinf(toRads(param_char_direc_angle_about_Z)); 
	float temp_eye_z = focusCharacter->char_loc_z + 10;
	
	// Camera at or look direction cart coords 
	// at vector...  1 is controllering the up and down since I am looking from a heigh of 1 at a height of 1
	float temp_at_x = focusCharacter->char_loc_x; 
	float temp_at_y = focusCharacter->char_loc_y;
	float temp_at_z = focusCharacter->char_loc_z + deltaDragY;

	// Camera up vector cart coords 
	// up vector... standing up
	float temp_up_x = 0.0; 
	float temp_up_y = 0.0;
	float temp_up_z = 1.0;

	gluLookAt(
			temp_eye_x, temp_eye_y, temp_eye_z,  // eye/camera position... where is the camera. Starts 25 units above orgin/character. 
			temp_at_x, temp_at_y, temp_at_z,	   // looking direction/at vector... for above should always be at character
			temp_up_x, temp_up_y, temp_up_z		   // alines top of camera with the y-axiz so that y is up.
	);

	//Switch to setting the camera perspective
	glMatrixMode(GL_PROJECTION); // projection matrix is activea
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    
	gluPerspective(45.0,                  //The camera angle
                   aspectRatio,           //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   100.0);                //The far z clipping coordinate

	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}
void Camera::setUpCameraFirst(float param_char_direc_angle_about_Z){
	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	angleAroundZ = param_char_direc_angle_about_Z;
	float temp_eye_x = focusCharacter->char_loc_x;  
	float temp_eye_y = focusCharacter->char_loc_y; 
	float temp_eye_z = focusCharacter->char_loc_z + 1.0;
	
	// Camera at or look direction cart coords 
	// at vector...  1 is controllering the up and down since I am looking from a heigh of 1 at a height of 1
	float temp_at_x = focusCharacter->char_loc_x + cosf(toRads(param_char_direc_angle_about_Z)); 
	float temp_at_y = focusCharacter->char_loc_y + sinf(toRads(param_char_direc_angle_about_Z));
	//float temp_at_x = focusCharacter->char_loc_x; 
	//float temp_at_y = focusCharacter->char_loc_y;
	float temp_at_z = focusCharacter->char_loc_z + 1.0 + deltaDragY;

	// Camera up vector cart coords 
	// up vector... standing up
	float temp_up_x = 0.0; 
	float temp_up_y = 0.0;
	float temp_up_z = 1.0;
	
	gluLookAt(
			temp_eye_x, temp_eye_y, temp_eye_z,  // eye/camera position... where is the camera. Starts 25 units above orgin/character. 
			temp_at_x, temp_at_y, temp_at_z,	   // looking direction/at vector... for above should always be at character
			temp_up_x, temp_up_y, temp_up_z		   // alines top of camera with the y-axiz so that y is up.
	);
	
	//Switch to setting the camera perspective
	glMatrixMode(GL_PROJECTION); // projection matrix is activea
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    
	gluPerspective(50.0,                  //The camera angle
                   aspectRatio,           //The width-to-height ratio
                   2.0,                   //The near z clipping coordinate
                   1000.0);                //The far z clipping coordinate

	glMatrixMode(GL_MODELVIEW); // return to modelview mode
}

//----------------------------------------------------------------------
// World::update - update the world after each idle event
//
// Moves the camera (when up/down arrow key held) forward or backward by
// the amount saved in deltaMove.
//----------------------------------------------------------------------
void Camera::update(float param_char_direc_angle_about_Z, int param_cameraMode) // update (with each idle event)
{
	angleAroundZ = param_char_direc_angle_about_Z;
	if(param_cameraMode == ABOVE){
		if (deltaMoveY) { // update camera position
			//y += deltaMoveY * ly * 0.1;
			focusCharacter->char_loc_y += deltaMoveY * 0.1;
		}
		if(deltaMoveX){
			//x += deltaMoveX * lx * 0.1;
			focusCharacter->char_loc_x += deltaMoveX * 0.1;
		}
	}else if(param_cameraMode == BEHIND || param_cameraMode == FIRST_PERSON){
			if (deltaMoveY) { // update camera position
				float YMovement = deltaMoveY * 0.1 * sin(toRads(param_char_direc_angle_about_Z)); 
				float XMovement = deltaMoveY * 0.1 * cos(toRads(param_char_direc_angle_about_Z)); 				
				
				focusCharacter->char_loc_y += YMovement;
				focusCharacter->char_loc_x += XMovement;
			}
	
			if(deltaMoveX){
				float YMovement = deltaMoveX * 0.1 * -1 * cos(toRads(param_char_direc_angle_about_Z)); 
				float XMovement = deltaMoveX * 0.1 * sin(toRads(param_char_direc_angle_about_Z)); 				
				
				focusCharacter->char_loc_y += YMovement;
				focusCharacter->char_loc_x += XMovement;
			}
	}else{
		cout << "Update Camera Error: invaild Camera Mode" << endl;
	}
	glutPostRedisplay(); // redisplay everything
}