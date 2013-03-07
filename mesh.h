#ifndef __MESH_H__
#define __MESH_H__

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#pragma comment(lib, "glew32.lib")
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;
namespace lab3 {

typedef struct {
	float pos[3];
	float norm[3];
} Vertex;

typedef struct {
	int index[3];
} Triangle;

class Mesh {
private:
	vector<Vertex> verts;
	vector<Triangle> triangles;
	float *triangle_norms;

	void build_triangle_norms();
	void cross(float x[], float y[], float r[]);
	float normalize(float *x, float *r=0);
public:
	~Mesh();
	void read_obj_file(const char* filename);
	void rebuild_vertex_norms();
	void write_obj_file(const char* filename);
};

}

#endif
