RGBpixmap:
----------
Contains code for manipulating .bmp files, based on the RGBpixmap object
given in the book "Computer Graphics using Open GL" by F. S. Hill.   The
files are RGBpixmap.h and RGBpixmap.cpp.

The file RGBpixmap.h defines two objects:

    RGBpixel: a single RGB color as three unsigned char's.
        It supports a copy constructor and a constructor which is
        given three unsigned characters for R, G, and B.

    RGBpixmap: a pixel array, called pixel, where each individual pixel
        is of type RGBpixel.  The constructor is given the number of
        rows and columns in the pixel map.  Here are its principal
        methods:

        void setPixel(int col, int row, const RGBpixel& P)
            Sets the pixel color in the given row and column in the
            pixel map to the color P.

        RGBpixel getPixel(int col, int row)
            Returns the pixel color in a the given row and column in
            the image.

        bool readBMPFile(const string& fname,
                        bool glPad=false,
                        bool verbose=false);

            Reads a pixel map from the given .bmp file name, fname.  If
            the argument glPad is true, then the image is padded out so
            its height and width are both powers of 2 (this is required
            for texture mapping in OpenGL). If the verbose argument is
            true, it outputs statistical information about the input
            file for debugging purposes. It returns false if there is
            an error (the file cannot be opened or format error).

        bool writeBMPFile(const string& fname);
            Outputs the pixel map as a .bmp file, fname.  It returns
            false if an error occured (cannot open the file).

Note that .bmp files have an usual row numbering convention, namely that
rows are numbered from bottom-up, not top-down.  This program does
nothing to alter the row numbering.

======================================================================
Sample 1: Using RGBpixmap for Texture Mapping in OpenGL
======================================================================

(This assumes a single texture.)

  #include "RGBpixmap.h"
  
  //------------------------------------------------------------------
  // Read texture from a .bmp file (done once per texture file). The
  // file name is a path relative to the working directory where the
  // program runs.
  //
  // If you see the error message below, determine the working directory
  // in which your program executes, and set the path to the .bmp file
  // relative to this directory.
  //------------------------------------------------------------------
  if (!myPixmap.readBMPFile("text0.bmp", true, true)) {
      cerr << "File text0.bmp cannot be read or illegal format" << endl;
      exit(1);
  }
  //------------------------------------------------------------------
  //  OpenGL initializations (done once for each texture)
  //------------------------------------------------------------------
  RGBpixmap myPixmap;
  GLuint texID;                               // OpenGL texture ID
  glGenTextures(1, &texID);                   // generate texture ID
  glBindTexture(GL_TEXTURE_2D, texID);        // set the active texture

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // store pixels by byte

  glTexImage2D(                               // present texture to OpenGL
      GL_TEXTURE_2D,                          // texture is 2-d
      0,                                      // resolution level 0
      GL_RGB,                                 // internal format
      myPixmap.nCols,                         // image width
      myPixmap.nRows,                         // image height
      0,                                      // no border
      GL_RGB,                                 // my format
      GL_UNSIGNED_BYTE,                       // my type
      myPixmap.pixel);                        // the pixels

                                              // build mipmaps
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, myPixmap.nCols, myPixmap.nRows, GL_RGB, GL_UNSIGNED_BYTE, myPixmap.pixel);
  //
  // ... (repeat the above for each texture to be used)
  //

  //------------------------------------------------------------------
  //  Set texture parameters
  //  (If you have only one texture, these can be set once. If you have
  //  multiple textures and the parameter settings are different for
  //  each, you should update these settings prior to drawing the new
  //  texture.)
  //
  //  These are reasonable defaults. See the OpenGL documentation for
  //  other possible values.
  //------------------------------------------------------------------

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //------------------------------------------------------------------
  // Select ONE of the following options:
  //   GL_DECAL - best for prelit textures (e.g., skybox)
  //   GL_MODULATE - best for standard surface textures
  //   ... there are a number of others for different effects
  //------------------------------------------------------------------
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  //------------------------------------------------------------------
  //  Draw a textured object
  //  We assume that all the above initializations have been performed.
  //
  //  If GL_MODULATE is used, the color should be set to the actual
  //  object color. If GL_DECAL is used, the color choice does not
  //  really matter.
  //------------------------------------------------------------------
  glEnable(GL_TEXTURE_2D);                    // enable texture mapping
 
  GLfloat color[] = {1.0, 1.0, 1.0, 1.0};     // set surface RGBA color
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

  glBegin(GL_POLYGON);                        // draw the object
      glNormal3f  (/*...specify normal  coordinates for vertex 0...*/);
      glTexCoord2f(/*...specify texture coordinates for vertex 0...*/);
      glVertex3f  (/*...specify vertex  coordinates for vertex 0...*/);
      // ... (repeat for other vertices)
  glEnd();
  glDisable(GL_TEXTURE_2D);                   // disable texture mapping



======================================================================
Sample 2: Using RGBpixmap to generate a bmp file for ray tracing
======================================================================

  #include "RGBpixmap.h"

  // ...

  RGBpixmap  *thePixmap = new RGBpixmap(nRows, nCols); // allocate pixel map
  if (!thePixmap->pixel) {                             // allocation error?
      // ...error: Cannot allocate pixel map...
  }

  // ...

  for (int row = 0; row < nRows; row++) {
      for (int col = 0; col < nCols; col++) {
          // ...shoot ray for row and col and get pixel color...
          RGBpixel pixColor = cast final pixel colors (see note below)
          thePixmap->setPixel(col, row, pixColor);     // store in pixmap
      }
  }
  thePixmap->writeBMPFile(bmpFileName);                // output .bmp file


To cast a floating point color C (given as (C.r, C.g, C.b)) to a
RGBpixel.  First clamp the color to the range from 0 to 1, and then cast
it using:

        pixColor.r = RGB_uchar(C.r * RGB_MAX);
        pixColor.g = RGB_uchar(C.g * RGB_MAX);
        pixColor.b = RGB_uchar(C.b * RGB_MAX);

RGB_uchar is typdefed to "unsigned char" and RGB_MAX is defined to be
255 in the file "RGBpixel.h".)
