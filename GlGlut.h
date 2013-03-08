#ifndef __GLGLUT_H__
#define __GLGLUT_H__

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "glew32.lib")
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "mesh.h"
#include "MY_MATH.h"
#include "MY_GLSL.h"

#define DEF_SCREEN_W 800
#define DEF_SCREEN_H 800
#define WINDOW_TITLE "CSE 5542 Lab 3 - Dan Ziemba"
#define XFORM_NONE 0
#define XFORM_ROTATE 1
#define XFORM_SCALE 2

namespace lab3 {

class GlGlut {
private:

protected:
	static GlGlut *instance;
	int screen_width;
	int screen_height;
	Mesh *mesh;
	GLuint programObject;

	int xform_mode;
	int press_x, press_y;
	float x_angle,y_angle;
	float scale_size;

	static const GLfloat ambient[4];
	static const GLfloat light0Position[4];
	static const GLfloat ambient0[4];
	static const GLfloat diffuse0[4];
	static const GLfloat specular0[4];
	static const GLfloat spotDir0[3];

	bool light0;

	// Glut callbacks
	void display();
	void idle();
	void keyboard(unsigned char key, int mousex, int mousey);
	void mouseClick(int button, int state, int x, int y);
	void mouseMotion(int x, int y);
	void reshape(int w, int h);

	////  Static wrappers used to register glut callbacks
	static void displayWrapper();
	static void idleWrapper();
	static void keyboardWrapper(unsigned char key, int mousex, int mousey);
	static void mouseClickWrapper(int button, int state, int x, int y);
	static void mouseMotionWrapper(int x, int y);
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
