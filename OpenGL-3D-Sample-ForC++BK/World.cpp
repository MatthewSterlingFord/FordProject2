//----------------------------------------------------------------------
// Best viewed with tabs every 2 columns
//----------------------------------------------------------------------
//	File: World.cpp - World methods
//----------------------------------------------------------------------

#include <cstdlib>     // C++ standard definitions
#include <cstdio>      // C I/O (for sprintf) 
#include <iostream>    // C++ I/O

//#include <stdout>
#include <cmath> // math definitions
// include files are in a slightly different location for MacOS

using namespace std;                    // make std accessible

#include "World.h" // World definitions

//----------------------------------------------------------------------
// World::World - initialize the world
//
// Initializes the camera position, resets various flags, and generates
// a 6x6 grid of snowmen, which are stored in a list.
//----------------------------------------------------------------------
World::World() // World constructor
{
	character = new Character(); // char
	camera = new Camera(character);
	// Mouse drag control
	isDragging = false; // true when dragging
	xDragStart = 0; // records the x-coordinate when dragging starts
	yDragStart = 0; // records the x-coordinate when dragging starts
	int cameraMode = 0;

	// Create 36 snowmen and append each to snowman list
	for(int i = -3; i < 3; i++) {
		for(int j = -3; j < 3; j++) {
			if(!(i == 0 && j == 0)){
				snowmen.push_back(Snowman(i*7.5, j*7.5));
			}
		}

	}
}


//----------------------------------------------------------------------
// World::setAspectRatio - set window's aspect ratio
//----------------------------------------------------------------------
void World::setAspectRatio(float ratio) 
{
	camera->aspectRatio = ratio;
}

void printErrorMessageAndExit(const char * message){
		//throw std::runtime_error(message);
		cout << message << endl;
}

void drawXYZAxis(){
  // Draws
  // Red x-axis
  // Green y-axis 
  // Blue z-axis. 
  glBegin(GL_LINES);
    glColor3fv(RED_RGB); glVertex3f(0, 0, 0); glVertex3f(100, 0, 0);
    glColor3fv(GREEN_RGB); glVertex3f(0, 0, 0); glVertex3f(0, 100, 0);
    glColor3fv(BLUE_RGB); glVertex3f(0, 0, 0); glVertex3f(0, 0, 100);
  glEnd();

}

void drawGround(GLuint passed_ground_texture_id){
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	
	// draw the ground - 200x200 square colored green
	glEnable(GL_TEXTURE_2D); // enable texturing
	//glTexParameteri(GL_TEXTURE_2D, GL_GEN);
	glBindTexture(GL_TEXTURE_2D, passed_ground_texture_id); // select the active texture
	
	// (use GL_REPLACE below for skyboxes)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glColor3fv(WHITE_RGB);

	glBegin(GL_QUADS); // draw the object(s)
	//Bottom Left
	glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
	glTexCoord2f(0.0f,0.0f); // set texture coords
	glVertex3f(-100.0, -100.0, 0.0);
	//Bottom Right
	glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
	glTexCoord2f(20.0f,0.0f); // set texture coords
	glVertex3f(100.0, -100.0, 0.0);
	//Top Right
	glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
	glTexCoord2f(20.0f,20.0f); // set texture coords
	glVertex3f(100.0, 100.0, 0.0);
	//Top Left
	glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
	glTexCoord2f(0.0f,20.0f); // set texture coords
	glVertex3f(-100.0, 100.0, 0.0);
	
	// ... (repeat for other vertices)
	glEnd();

	glDisable(GL_TEXTURE_2D); // disable texturing

	glEnable(GL_LIGHTING); // Now can use lighting 
	glEnable(GL_COLOR_MATERIAL);
	//Old just green grass	
	//glColor3fv(GRASS_GREEN_RGB);
	//glBegin(GL_QUADS);
	//	glVertex3f(-100.0, -100.0, 0.0);
	//	glVertex3f(-100.0,  100.0, 0.0);
	//	glVertex3f( 100.0,  100.0, 0.0);
	//	glVertex3f( 100.0, -100.0, 0.0);
	//glEnd();
}

void drawSky(GLuint passed_sky_texture_id){
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	
	// draw the ground - 200x200 square colored green
	glEnable(GL_TEXTURE_2D); // enable texturing
	//glTexParameteri(GL_TEXTURE_2D, GL_GEN);
	glBindTexture(GL_TEXTURE_2D, passed_sky_texture_id); // select the active texture
	
	// (use GL_REPLACE below for skyboxes)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// reasonable filter choices
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glColor3fv(WHITE_RGB);

	//Draw west face
	glBegin(GL_QUADS); // draw the object(s)
		//Bottom Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.0f,0.25f); // set texture coords
		glVertex3f(-100.0, 100.0, 0.0);
		//Bottom Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.25f); // set texture coords
		glVertex3f(-100.0, 100.0, 100.0);	
		//Top Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.75f); // set texture coords
		glVertex3f(-100.0, -100.0, 100.0);
		//Top Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.0f,0.75f); // set texture coords
		glVertex3f(-100.0, -100.0, 0.0);
	glEnd();

	//Draw North face
	glBegin(GL_QUADS); // draw the object(s)
		//Bottom Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.0f); // set texture coords
		glVertex3f(-100.0, 100.0, 0.0);
		//Bottom Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.0f); // set texture coords
		glVertex3f(100.0, 100.0, 0.0);	
		//Top Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.25f); // set texture coords
		glVertex3f(100.0, 100.0, 100.0);
		//Top Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.25f); // set texture coords
		glVertex3f(-100.0, 100.0, 100.0);
	glEnd();

	//Draw South face
	glBegin(GL_QUADS); // draw the object(s)
		//Bottom Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,1.0f); // set texture coords
		glVertex3f(-100.0, -100.0, 0.0);
		//Bottom Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,1.0f); // set texture coords
		glVertex3f(100.0, -100.0, 0.0);	
		//Top Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.75f); // set texture coords
		glVertex3f(100.0, -100.0, 100.0);
		//Top Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.75f); // set texture coords
		glVertex3f(-100.0, -100.0, 100.0);	
	glEnd();

	//Draw east face
	glBegin(GL_QUADS); // draw the object(s)
		//Bottom Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.25f); // set texture coords
		glVertex3f(100.0, 100.0, 100.0);
		//Bottom Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(1.0f,0.25f); // set texture coords
		glVertex3f(100.0, 100.0, 0.0);	
		//Top Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(1.0f,0.75f); // set texture coords
		glVertex3f(100.0, -100.0, 0.0);
		//Top Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.75f); // set texture coords
		glVertex3f(100.0, -100.0, 100.0);	
	glEnd();

	//Draw top face
	glBegin(GL_QUADS); // draw the object(s)
		//Bottom Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.25f); // set texture coords
		glVertex3f(-100.0, 100.0, 100.0);
		//Bottom Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.25f); // set texture coords
		glVertex3f(100.0, 100.0, 100.0);	
		//Top Right
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.75f,0.75f); // set texture coords
		glVertex3f(100.0, -100.0, 100.0);
		//Top Left
		glNormal3f(0.0f,0.0f,1.0f); // set the surface normal
		glTexCoord2f(0.25f,0.75f); // set texture coords
		glVertex3f(-100.0, -100.0, 100.0);	
	glEnd();

	glDisable(GL_TEXTURE_2D); // disable texturing

	glEnable(GL_LIGHTING); // Now can use lighting 
	glEnable(GL_COLOR_MATERIAL);
	//Old just green grass	
	//glColor3fv(GRASS_GREEN_RGB);
	//glBegin(GL_QUADS);
	//	glVertex3f(-100.0, -100.0, 0.0);
	//	glVertex3f(-100.0,  100.0, 0.0);
	//	glVertex3f( 100.0,  100.0, 0.0);
	//	glVertex3f( 100.0, -100.0, 0.0);
	//glEnd();
}

//----------------------------------------------------------------------
// World::draw - draw everything
//
// Moves the camera (when up/down arrow key held) forward or backward by
// the amount saved in deltaMove.
//----------------------------------------------------------------------
void World::draw()
{
	// Everything lit by at least this amount 
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f}; 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);	

	GLfloat lt0Intensity[4] = {1.5, 1.5, 1.5, 1.0}; // white
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0Intensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR
		, lt0Intensity);
	GLfloat lt0Position[4] = {-100.0, 100.0, 100.0, 1.0}; // location
	glLightfv(GL_LIGHT0, GL_POSITION, lt0Position);
	
	// attenuation params (a,b,c)
	//glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	//glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	//glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	glEnable(GL_LIGHT0);
	
	if(cameraMode == DEFULT){
		camera-> setUpCameraDefault(); // set up the camera
	}else if(cameraMode == ABOVE){
		camera-> setUpCameraAbove(character->char_direc_angle_about_Z); // set up the camera
	}else if(cameraMode == BEHIND){
		camera-> setUpCameraBehind(character->char_direc_angle_about_Z);
	}else if(cameraMode == FIRST_PERSON){
		camera-> setUpCameraFirst(character->char_direc_angle_about_Z);
	}else{
		printErrorMessageAndExit("CameraMode Invalid");
	}

	drawGround(ground_texture_id);
	//TODO Finish
	drawSky(sky_texture_id);

	// draw all the snow men
	// (older versions of C++ don't have range iterators!)
	#ifdef NO_CPP11
		std::list<Snowman>::iterator s = snowmen.begin();
		while (s != snowmen.end()) { // iterate through all in list
			s->draw();
		}
	#else
		for (Snowman s : snowmen) { // iterate through all in list
			s.draw();
		}
	#endif
	
	character -> draw();
	// Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
  // axes are ten units long.
	drawXYZAxis();
}

void up(Camera* camera, int cameraMode, Character* character){
			if(cameraMode == ABOVE){
				camera->deltaMoveY = 1.0; 
				character->char_direc_angle_about_Z = 90;
			}else if(cameraMode == BEHIND){
				camera->deltaMoveY = 1.0;
			}else if(cameraMode == FIRST_PERSON){
				camera->deltaMoveY = 1.0; 
			}else{
				printErrorMessageAndExit("CameraMode Invalid");	
			}
			glutPostRedisplay(); 
}
void down(Camera* camera, int cameraMode, Character* character){
			if(cameraMode == ABOVE){
				camera->deltaMoveY = -1.0; 
				character->char_direc_angle_about_Z = 270;
			}else if(cameraMode == BEHIND){
				camera->deltaMoveY = -1.0; 
			}else if(cameraMode == FIRST_PERSON){
				camera->deltaMoveY = -1.0; 
			}else{
				printErrorMessageAndExit("CameraMode Invalid");	
			}
			glutPostRedisplay(); 
}
void left(Camera* camera, int cameraMode, Character* character){
			if(cameraMode == ABOVE){
				camera->deltaMoveX = -1.0; 
				character->char_direc_angle_about_Z = 180;
			}else if(cameraMode == BEHIND){
				camera->deltaMoveX = -1.0; 
			}else if(cameraMode == FIRST_PERSON){
				camera->deltaMoveX = -1.0; 
			}else{
				printErrorMessageAndExit("CameraMode Invalid");	
			}
			glutPostRedisplay(); 
}
void right(Camera* camera, int cameraMode, Character* character){
			if(cameraMode == ABOVE){
				camera->deltaMoveX = 1.0; 
				character->char_direc_angle_about_Z = 0;
			}else if(cameraMode == BEHIND){
				camera->deltaMoveX = 1.0; 
			}else if(cameraMode == FIRST_PERSON){
				camera->deltaMoveX = 1.0; 
			}else{
				printErrorMessageAndExit("CameraMode Invalid");	
			}
			glutPostRedisplay(); 
}


//----------------------------------------------------------------------
// Process keyboard events
// 
// When one of the arrow keys is first depressed, we set deltaMove.
// With each subsequent idle event, we move the camera by this amount
// based on the direction it is currently pointing.
//----------------------------------------------------------------------
void World::processNormalKeys(unsigned char key, int xx, int yy)
{
	const int ESC = 27; // escape key (for exit)
	switch (key) {
	case 'r':
		character = new Character();
		camera = new Camera(character);
	break;
	case ESC:
	case 'q':
	case 'Q':
		exit(0);
	break;
	case 'z':
		cameraMode = DEFULT;
		glutPostRedisplay();
	break;
	case 'm':
	case 'M':
		if(cameraMode == ABOVE || cameraMode == DEFULT){
			cameraMode = BEHIND;
			cout << "M key pressed detected. Switching to Mode:BEHIND. \n \t" << 
					"Character eye/postion vector:" << "char_loc_x=" << character->char_loc_x << " char_loc_y=" << character->char_loc_y << " char_loc_z=" << character->char_loc_z <<
					         //  "TODO NOT RIGHT Camera eye vector:" << "char_loc_x=" << character->char_loc_x << " char_loc_y=" << character->char_loc_y << " char_loc_z=" << character->char_loc_z <<
					         //  "Camera at  vector:" << "at_x=" << camera->at_x << " at_y=" << camera->at_y << " at_z= " << camera->at_z << 
							 //  "Camera up  vector:" << "up_x=" << camera->up_x << " up_y=" << camera->up_y << " up_z= " << camera->up_z<< 
							 endl;
		}else if(cameraMode == BEHIND){
		//	cout << "Draw character with X:" << camera->x << "Y:" << camera->y << endl;
			cameraMode = FIRST_PERSON;
		}else if(cameraMode == FIRST_PERSON){
		//	cout << "Draw character with X:" << camera->x << "Y:" << camera->y << endl;
			cameraMode = ABOVE;
		}else{
			printErrorMessageAndExit("CameraMode Invalid");	
		}
		glutPostRedisplay(); 
	break;
	case 'h':
	case 'H':
		character -> char_loc_z += 1;
	break;
	case 'l':
	case 'L':
		if(character -> char_loc_z > 1){
			character -> char_loc_z -= 1;
		}
		glutPostRedisplay();
	break;
	
	case 'w':
	case 'W':
		up(camera, cameraMode, character);
	break;
	case 's':
	case 'S':	
		down(camera, cameraMode, character);
	break;
	case 'd':
	case 'D':
		right(camera, cameraMode, character);		
	break;
	case 'a':
	case 'A':
		left(camera, cameraMode, character);
	break;
	}
} 

void World::pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : 
			up(camera, cameraMode, character);
		break;			
		case GLUT_KEY_DOWN : 	
			down(camera, cameraMode, character);
		break;
		
		case GLUT_KEY_LEFT :
			left(camera, cameraMode, character);
		break;

		case GLUT_KEY_RIGHT :
			right(camera, cameraMode, character);
		break;
	}
} 

void World::releaseSpecialKey(int key, int xx, int yy) 
{
	switch (key) {
		case GLUT_KEY_UP : camera->deltaMoveY = 0.0; break;
		case GLUT_KEY_DOWN : camera->deltaMoveY = 0.0; break;
		case GLUT_KEY_RIGHT : camera->deltaMoveX = 0.0; break;
		case GLUT_KEY_LEFT : camera->deltaMoveX = 0.0; break;
	}
} 



//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void World::mouseMove(int xx, int yy) 
{ 	
	if (isDragging) { // only when dragging
		// update the change in angle
		camera->deltaDragX = (xx - xDragStart) * 0.005;
		character->char_direc_angle_about_Z -= camera->deltaDragX;

		camera->deltaDragY = (yy - yDragStart) * 0.0005;


		// camera's direction is set to angle + deltaAngle
		//camera->lx = -sin(camera->angle + camera->deltaAngle);
		
		//camera->ly = cos(camera->angle + camera->deltaAngle);
		glutPostRedisplay(); 
	}
}

void World::mouseButton(int button, int state, int xx, int yy) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = true; // start dragging
			xDragStart = xx; // save x where button first pressed
			yDragStart = yy; // save x where button first pressed
		}
		else if (state == GLUT_UP){ 
			//isDragging = true; // start dragging
			//yDragStart = yy; // save x where button first pressed
			isDragging = false; // no longer dragging	
			//float theta = atanf(yDragStart/(xDragStart + xx));
			//camera->angleAroundZ += theta; // update camera turning angle
			//float xt = xDragStart + (camera->deltaDragX);
			//float yt = yDragStart + (camera->deltaDragY);
			//float zt = (camera ->z);		
			//float r = sqrtf(xt*xt + yt * yt + zt * zt);
			//float omaga = acosf((camera ->z)/r);
			//camera->angleAroundX += theta; // update camera turning angle
		}
	}
}
