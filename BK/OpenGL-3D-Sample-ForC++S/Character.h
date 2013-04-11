//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
// File: Snowman.h - Snowman definitions
//----------------------------------------------------------------------
#ifndef CHARACTER_H
#define CHARACTER_H
#include "../OpenGL-3D-Sample-ForC++/OpenGL-3D-Sample-ForC++/type.h"
//----------------------------------------------------------------------
// Snowman
// A snowman is a rather uninteresting object. It just sits at some
// (x,y) position on the ground, and has the capability of being drawn.
//----------------------------------------------------------------------

class Character {
private:
public:
	float char_loc_x, char_loc_y, char_loc_z, char_direc_angle_about_Z, alapedTime, alapedWingTime;	// location
	float char_dir_x, char_dir_y, char_dir_z;
	Character();
	void draw(); // draw him
	void update(int movingXorY, float time);
};

#endif
