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
//******************************************************************************
// MY_MATH
// This file contains some basic matrix/vector operation functions
//
// Modified to move function definitions out of header file
//******************************************************************************
#ifndef __MY_MATH_H__
#define __MY_MATH_H__
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>

//******************************************************************************
//  3D Vector Operations
//******************************************************************************
float Normalize_3D(float V[3]);
void Cross_3D(float A[3], float B[3], float C[3]);

//******************************************************************************
//  Matrix-Matrix Multiplication: C=A*B
//******************************************************************************
void Matrix_Multiplication(float A[4][4], float B[4][4], float C[4][4]);

//******************************************************************************
//  Matrix Rotation
//******************************************************************************
void Matrix_Rotate(float angle, float x, float y, float z, float M[4][4]);

//******************************************************************************
//  Matrix Scale
//******************************************************************************
void Matrix_Scale(float sx, float sy, float sz, float M[4][4]);

//******************************************************************************
//  Matrix Translate
//******************************************************************************
void Matrix_Translate(float x, float y, float z, float M[4][4]);

//******************************************************************************
//  Perspective Projection Matrix
//******************************************************************************
void Matrix_Perpsective(float fov, float aspect, float near, float far,
                        float M[4][4]);

//******************************************************************************
//  Look_At Matrix
//******************************************************************************
void Matrix_LookAt(float ex, float ey, float ez, float tx, float ty, float tz,
                   float ux, float uy, float uz, float R[4][4]);


//******************************************************************************
//  Matrix Transpose
//******************************************************************************
void Matrix_Transpose(float A[4][4], float B[4][4]);

#endif
