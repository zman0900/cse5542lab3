#ifndef __GLGLUT_H__
#define __GLGLUT_H__

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#pragma comment(lib, "glew32.lib")
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "mesh.h"
#include "MY_MATH.h"

#define DEF_SCREEN_W 800
#define DEF_SCREEN_H 800
#define WINDOW_TITLE "CSE 5542 Lab 3 - Dan Ziemba"

namespace lab3 {

class GlGlut {
private:

protected:
	static GlGlut *instance;
	int screen_width;
	int screen_height;
	Mesh *mesh;
	
	// Glut callbacks
	void display();
	void idle();
	void keyboard(unsigned char key, int mousex, int mousey);
	void mouseClick(int button, int state, int x, int y);
	void reshape(int w, int h);

	////  Static wrappers used to register glut callbacks
	static void displayWrapper();
	static void idleWrapper();
	static void keyboardWrapper(unsigned char key, int mousex, int mousey);
	static void reshapeWrapper(int w, int h);
public:
	GlGlut();
	~GlGlut();

	// Called by start to make wrappers work
	void setInstance();
	// Starts scene, does not return
	void start(int *argc, char *argv[]);
};

} // namespace lab3

#endif
