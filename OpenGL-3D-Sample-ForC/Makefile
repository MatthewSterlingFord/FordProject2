#-----------------------------------------------------------------------
#  Look for "--->" for things that you need to change for your
#  particular configuration.
#-----------------------------------------------------------------------
#  This simple Makefile which compiles a single C++ program, in the
#  source file $TARGET.cpp (where the variable TARGET is set below)
#  assuming a Unix system for OpenGL, GLUT, and X-windows.  The directories
#  for OpenGL and GLUT will need to be changed depending on your system.
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# ---> INSERT THE NAME OF YOUR SOURCE FILE HERE
#-----------------------------------------------------------------------

TARGET = opengl-3D-sample

#-----------------------------------------------------------------------
#  Variable settings: Set these according to your system configuration
#
#  Compiler/Linker settings:
#  -------------------------
#	C++		Your favorite C++ compiler (or C compiler).
#	CFLAGS		Your compilation flags.
#	    -g		    compile for debugging (e.g., dbx or gdb).
#	    -O3		    optimize code for speed
#	    -Wall	    give all warnings (highly recommended with
#			    OpenGL programs)
#	MISC_LIBS	Any miscellaneous libraries that your program
#			needs.
#			    add -lm here for math library
#			    add -lposix4 here for clock_gettime()
#			    (a real-time clock on Solaris machines).
#
#  System/Platform-dependent settings (which you will need to set):
#  ----------------------------------------------------------------
#	OGL_DIR		Directory where OpenGL branches off (OGL_DIR/GL)
#	OGL_LIBS	OpenGL library names
#	X_DIR		X11 lib directory (where libX11, libXext live)
#
#  System/Platform-dependent settings (you should not need to set):
#  ----------------------------------------------------------------
#	OGL_LIB_DIR	OpenGL/Glut library directory (where libGL.so lives)
#	OGL_INC_DIR	OpenGL linclude directory (where GL/gl.h lives)
#	OGL_LFLAGS	Loader flags for OpenGL stuff
#	X_LFLAGS	Loader flags for X11 stuff
#	LD_FLAGS	All loader flags
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# ---> USE THESE DEFINITIONS FOR CSIC Linux Cluster Machines
#-----------------------------------------------------------------------
OGL_DIR = /usr
OGL_LIBS =  -lGLU -lGL -lglut
X_DIR = /usr/lib

#-----------------------------------------------------------------------
# Setting for C++ compilation
# ---> Set C++ or CC to your C++ or C compiler
# ---> Set CFLAGS according your desired option (debug/performance)
#	-Wall		List all warnings (highly recommended)
#	-O3		Optimize
#	-g		Allow debugging
#	-lm		Math library
#-----------------------------------------------------------------------
C++ = g++
CC = gcc
# CFLAGS = -g -Wall				(for debugging)
# CFLAGS = -O3 -Wall				(for best performance)
CFLAGS = -O3 -Wall
MISC_LIBS =  -lm

#-----------------------------------------------------------------------
# These are derived from the above
#-----------------------------------------------------------------------
OGL_LIB_DIR  = $(OGL_DIR)/lib
OGL_INC_DIR  = $(OGL_DIR)/include

OGL_LFLAGS   = -L$(OGL_DIR)/lib -Wl,-rpath=/usr/local/freeglut/lib $(OGL_LIBS)
INC_FLAGS = -I$(OGL_INC_DIR)
LD_FLAGS = $(OGL_LFLAGS) $(X_LFLAGS) $(MISC_LIBS)
X_LFLAGS = -L$(X_DIR) -lX11 -lXext -lXmu -lXi 

#-----------------------------------------------------------------------
# Compilation
#	This is the simplest form assuming a single source file.
#	If the file name is foo.cpp, set TARGET = foo, and the
#	object file will be put in foo.o, and the executable will
#	be put in foo.
#-----------------------------------------------------------------------

default: $(TARGET)

#-----------------------------------------------------------------------
# Use this for C files
#-----------------------------------------------------------------------
$(TARGET).o: $(TARGET).c
	$(CC) -c $(CFLAGS) $(INC_FLAGS) $(TARGET).c

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) $(TARGET).o -o $(TARGET) $(LD_FLAGS)

#-----------------------------------------------------------------------
#  Clean-up
#	make clean		remove .o and core files
#	make realclean		also removes executable
#-----------------------------------------------------------------------
clean:
	rm -f *.o core

realclean: clean
	rm -f $(TARGET)
