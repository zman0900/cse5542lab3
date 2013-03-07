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
// Modified to move function definitions out of header file and use pi constant
//******************************************************************************

float Normalize_3D(float V[3])
{
	float m=sqrtf(V[0]*V[0]+V[1]*V[1]+V[2]*V[2]);
	if(m<1e-14f)	return m;
	V[0]/=m;
	V[1]/=m;
	V[2]/=m;
	return m;
}

void Cross_3D(float A[3], float B[3], float C[3])
{
	//C=A X B
	C[0]= A[1]*B[2]-B[1]*A[2];
	C[1]=-A[0]*B[2]+B[0]*A[2];
	C[2]= A[0]*B[1]-B[0]*A[1];
}

//******************************************************************************
//  Matrix-Matrix Multiplication: C=A*B
//******************************************************************************
void Matrix_Multiplication(float A[4][4], float B[4][4], float C[4][4])
{
	float R[4][4];
	memset(&R[0][0], 0, sizeof(float)*16);
	for(int i=0; i<4; i++)
	for(int j=0; j<4; j++)
	for(int k=0; k<4; k++)	
		R[i][j]+=A[i][k]*B[k][j];	
	memcpy(&C[0][0], &R[0][0], sizeof(float)*16);
}

//******************************************************************************
//  Matrix Rotation
//******************************************************************************
void Matrix_Rotate(float angle, float x, float y, float z, float M[4][4])
{	
	float half_angle=angle*M_PI/360.0;
	float Axis[3]={x, y, z};
	Normalize_3D(Axis);

	float a=cosf(half_angle);
	float b=Axis[0]*sinf(half_angle);
	float c=Axis[1]*sinf(half_angle);
	float d=Axis[2]*sinf(half_angle);

	memset(&M[0][0], 0, sizeof(float)*16);
	M[3][3]=1;

	M[0][0]=a*a+b*b-c*c-d*d;
	M[0][1]=2*(b*c-a*d);
	M[0][2]=2*(b*d+a*c);
	M[1][0]=2*(b*c+a*d);
	M[1][1]=a*a-b*b+c*c-d*d;
	M[1][2]=2*(c*d-a*b);
	M[2][0]=2*(b*d-a*c);
	M[2][1]=2*(c*d+a*b);
	M[2][2]=a*a-b*b-c*c+d*d;
}

//******************************************************************************
//  Matrix Scale
//******************************************************************************
void Matrix_Scale(float sx, float sy, float sz, float M[4][4])
{	
	memset(&M[0][0], 0, sizeof(float)*16);
	M[0][0]=sx;
	M[1][1]=sy;
	M[2][2]=sz;
	M[3][3]=1;
}

//******************************************************************************
//  Matrix Translate
//******************************************************************************
void Matrix_Translate(float x, float y, float z, float M[4][4])
{	
	memset(&M[0][0], 0, sizeof(float)*16);
	M[0][0]=1;
	M[1][1]=1;
	M[2][2]=1;
	M[3][3]=1;
	M[0][3]=x;
	M[1][3]=y;
	M[2][3]=z;
}

//******************************************************************************
//  Perspective Projection Matrix
//******************************************************************************
void Matrix_Perpsective(float fov, float aspect, float near, float far,
                        float M[4][4])
{
	float f=1/tan(fov*M_PI/360.0);
	memset(&M[0][0], 0, sizeof(float)*16);
	M[0][0]=f/aspect;
	M[1][1]=f;
	M[2][2]=(near+far)/(near-far);
	M[2][3]=(2*near*far)/(near-far);
	M[3][2]=-1;
}

//******************************************************************************
//  Look_At Matrix
//******************************************************************************
void Matrix_LookAt(float ex, float ey, float ez, float tx, float ty, float tz,
                   float ux, float uy, float uz, float R[4][4])
{
	float F[3]={tx-ex, ty-ey, tz-ez};
	Normalize_3D(F);
	float UP[3]={ux, uy, uz};
	Normalize_3D(UP);
	float S[3];
	Cross_3D(F, UP, S);
	Normalize_3D(S);
	float U[3];
	Cross_3D(S, F, U);

	float A[4][4];
	memset(&A[0][0], 0, sizeof(float)*16);
	A[0][0]=S[0];
	A[0][1]=S[1];
	A[0][2]=S[2];
	A[1][0]=U[0];
	A[1][1]=U[1];
	A[1][2]=U[2];
	A[2][0]=-F[0];
	A[2][1]=-F[1];
	A[2][2]=-F[2];
	A[3][3]=1;

	float B[4][4];
	Matrix_Translate(-ex, -ey, -ez, B);

	Matrix_Multiplication(A, B, R);
}


//******************************************************************************
//  Matrix Transpose
//******************************************************************************
void Matrix_Transpose(float A[4][4], float B[4][4])
{
	for(int i=0; i<4; i++)
	for(int j=0; j<4; j++)
		B[j][i]=A[i][j];
}
