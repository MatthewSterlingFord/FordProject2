//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
// 
//----------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "../Character.h"
//----------------------------------------------------------------------
// 
// 
//----------------------------------------------------------------------

class Camera {
private:
	
public:
	Character* focusCharacter;

	float aspectRatio; // aspect ratio of graphics window
	
	//float char_loc_x, eye_y, eye_z; // cameras position
	
	float deltaMoveX; // amount of incremental movement (when dragging)
	float deltaMoveY; // amount of incremental movement (when dragging)
	float deltaMoveZ; // amount of incremental movement (when dragging)

	float at_x, at_y, at_z; // camera direction

	float up_x, up_y, up_z; // camera up vection 
	
	float angleAroundZ, angleAroundX; // angle of rotation for the camera direction
	float deltaDragX; // x change (when dragging)
	float deltaDragY; // y change (when dragging)

	Camera(Character* focusCharacter); // constructor
	void setUpCameraDefault();
	void setUpCameraAbove(float param_char_direc_angle_about_Z); // draw him
	void setUpCameraFirst(float param_char_direc_angle_about_Z); // draw him
	void setUpCameraBehind(float param_char_direc_angle_about_Z); // draw him
	void update(float param_char_direc_angle_about_Z, int param_cameraMode); // update (with each idle event)
};

class AboveCamera : public Camera {
	
};

#endif