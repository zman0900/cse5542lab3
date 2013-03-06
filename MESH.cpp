#include "MESH.h"

namespace cse {

float Normalize(float *x, float *r)
{
	if(r==0) r=x;
	float m=sqrtf(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
	if(m<1e-14f) return m;
	float inv_m=1/m;
	r[0]=x[0]*inv_m;
	r[1]=x[1]*inv_m;
	r[2]=x[2]*inv_m;
	return m;
}

void Cross(float x[], float y[], float r[])
{
	r[0]= x[1]*y[2]-y[1]*x[2];
	r[1]=-x[0]*y[2]+y[0]*x[2];
	r[2]= x[0]*y[1]-y[0]*x[1];
}


MESH::MESH()
{
	max_number	= 655360;
	number		= 0;
	t_number	= 0;
	X			= new float	[max_number*3];		
	T			= new int	[max_number*3];
	XN			= new float	[max_number*3];
	TN			= new float	[max_number*3];
}

MESH::~MESH()
{
	if(X)	delete []X;
	if(T)	delete []T;
	if(XN)	delete []XN;
	if(TN)	delete []TN;
}
	
void MESH::Write_OBJ_File(const char *filename)
{
	FILE *fp=fopen(filename, "w+");
	for(int v=0; v<number; v++)
		fprintf(fp, "v %f %f %f\n", X[v*3+0], X[v*3+1], X[v*3+2]);
	for(int v=0; v<number; v++)
		fprintf(fp, "vn %f %f %f\n", XN[v*3+0], XN[v*3+1], XN[v*3+2]);
	for(int t=0; t<t_number; t++)
	{
		fprintf(fp, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", 
			T[t*3+0]+1, T[t*3+0]+1, T[t*3+0]+1,
			T[t*3+1]+1, T[t*3+1]+1, T[t*3+1]+1,
			T[t*3+2]+1, T[t*3+2]+1, T[t*3+2]+1);
	}
	fclose(fp);
}

void MESH::Read_OBJ_File(char *filename)
{
	number=0;
	t_number=0;
	int vertex_normal_number=0;
	FILE *fp=fopen(filename, "r+");		
	while(feof(fp)==0)
	{
		char token[1024];
		fscanf(fp, "%s", &token);
		if(token[0]=='#' && token[1]=='\0')
		{
			int c;
			while(feof(fp)==0)
				if((c=fgetc(fp))=='\r' || c=='\n')	break;
		}
		else if(token[0]=='v' && token[1]=='\0')	//vertex
		{
			fscanf(fp, "%f %f %f\n", &X[number*3], &X[number*3+1], &X[number*3+2]); 
			number++;
		}
		else if(token[0]=='v' && token[1]=='t')
		{
			float temp[2];
			fscanf(fp, "%f %f\n", &temp[0], &temp[1]);
		}
		else if(token[0]=='v' && token[1]=='n')
		{
			fscanf(fp, "%f %f %f\n", 
				   &XN[vertex_normal_number*3], 
				   &XN[vertex_normal_number*3+1], 
				   &XN[vertex_normal_number*3+2]); 
			vertex_normal_number++;
		}
		else if(token[0]=='f' && token[1]=='\0')
		{
			int data[64];
			int data_number=0;
			memset(data, 0, sizeof(int)*64);
			
			while(feof(fp)==0)
			{
				fscanf(fp, "%d", &data[data_number++]);
				bool end=false;
				while(feof(fp)==0)
				{
					char token=fgetc(fp);
					if(token==' ' || token=='\t')	break;
					if(token=='\n'|| token=='\r')	{end=true; break;}
				}
				if(end)	break;
			}
			for(int i=1; i<data_number-1; i++)
			{
				T[t_number*3+0]=data[0  ]-1;
				T[t_number*3+1]=data[i  ]-1;
				T[t_number*3+2]=data[i+1]-1;
				t_number++;
			}
		}			
	}
	fclose(fp);		
}

void MESH::Scale(float s)
{
	for(int i=0; i<number*3; i++)	X[i]*=s;
}

void MESH::Build_TN()
{
	memset(TN, 0, sizeof(float)*number*3);
	for(int i=0; i<t_number; i++)
	{
		float *p0=&X[T[i*3+0]*3];
		float *p1=&X[T[i*3+1]*3];
		float *p2=&X[T[i*3+2]*3];
		
		float e0[3], e1[3];
		for(int i=0; i<3; i++)
		{
			e0[i]=p1[i]-p0[i];
			e1[i]=p2[i]-p0[i];
		}
		Cross(e1, e0, &TN[i*3]);
		Normalize(&TN[i*3]);
	}
}

void MESH::Build_XN()
{
	memset(XN, 0, sizeof(float)*number*3);
	Build_TN();

	for(int i=0; i<t_number; i++)
	{
		int v0=T[i*3+0];
		int v1=T[i*3+1];
		int v2=T[i*3+2];			
		XN[v0*3+0]+=TN[i*3+0];
		XN[v0*3+1]+=TN[i*3+1];
		XN[v0*3+2]+=TN[i*3+2];
		XN[v1*3+0]+=TN[i*3+0];
		XN[v1*3+1]+=TN[i*3+1];
		XN[v1*3+2]+=TN[i*3+2];
		XN[v2*3+0]+=TN[i*3+0];
		XN[v2*3+1]+=TN[i*3+1];
		XN[v2*3+2]+=TN[i*3+2];
	}
	for(int i=0; i<number; i++)	Normalize(&XN[i*3]);
}


void MESH::Render()
{
	Build_XN();
	for(int i=0; i<t_number; i++)
	{
		float *p0=&X[T[i*3+0]*3];
		float *p1=&X[T[i*3+1]*3];
		float *p2=&X[T[i*3+2]*3];

		glBegin(GL_TRIANGLES);			
        glNormal3fv(&XN[T[i*3+0]*3]);
		glVertex3fv(p0);			
        glNormal3fv(&XN[T[i*3+1]*3]);
		glVertex3fv(p1);			
        glNormal3fv(&XN[T[i*3+2]*3]);
		glVertex3fv(p2);			
        glEnd();
	}
}

}
