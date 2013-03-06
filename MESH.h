//**************************************************************************************
//  Copyright (C) 2002 - 2011, Huamin Wang
//  All rights reserved.
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//     1. Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//     2. Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//     3. The names of its contributors may not be used to endorse or promote
//        products derived from this software without specific prior written
//        permission.
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//**************************************************************************************
// MESH.h
//**************************************************************************************
#ifndef __WHMIN_MESH_H__
#define __WHMIN_MESH_H__

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#pragma comment(lib, "glew32.lib")
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>

namespace cse {

float Normalize(float *x, float *r=0);
void Cross(float x[], float y[], float r[]);

class MESH
{
public:
	int		max_number;
	//vertex data
	int		number;		//vertex number
	float*	X;			//vertex positions
	float*	XN;			//vertex normals
	//triangle data
	int		t_number;	//triangle number
	int*	T;			//triangle indices
	float*	TN;			//Triangle Normals

	MESH();
	~MESH();
		
	void Write_OBJ_File(const char *filename);
	void Read_OBJ_File(char *filename);
	void Scale(float s);
	void Build_TN();
	void Build_XN();
	void Render();
};

}

#endif
