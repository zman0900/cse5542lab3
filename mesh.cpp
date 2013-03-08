#include "mesh.h"

namespace lab3 {

void Mesh::build_triangle_norms() {
	if (triangle_norms) delete[] triangle_norms;
	triangle_norms = new float [triangles.size() * 3];

	for(int i=0; i<triangles.size(); i++) {
		float *p0 = verts[triangles[i].index[0]].pos;
		float *p1 = verts[triangles[i].index[1]].pos;
		float *p2 = verts[triangles[i].index[2]].pos;

		float e0[3], e1[3];
		for(int j=0; j<3; j++) {
			e0[j]=p1[j]-p0[j];
			e1[j]=p2[j]-p0[j];
		}
		cross(e1, e0, &triangle_norms[i*3]);
		normalize(&triangle_norms[i*3]);
	}
}

void Mesh::cross(float x[], float y[], float r[]) {
	r[0]= x[1]*y[2]-y[1]*x[2];
	r[1]=-x[0]*y[2]+y[0]*x[2];
	r[2]= x[0]*y[1]-y[0]*x[1];
}

void Mesh::init_vbo() {
	vbo_ready = true;
	glGenBuffers(1, &vertVBO);
	glGenBuffers(1, &triVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triVBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0],
	             GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(Triangle),
	             &triangles[0], GL_STATIC_DRAW);
}

float Mesh::normalize(float *x, float *r) {
	if(r==0) r=x;
	float m=sqrtf(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
	if(m<1e-14f) return m;
	float inv_m=1/m;
	r[0]=x[0]*inv_m;
	r[1]=x[1]*inv_m;
	r[2]=x[2]*inv_m;
	return m;
}

Mesh::Mesh() {
	vbo_ready = false;
	triangle_norms = NULL;
}

Mesh::~Mesh() {
	if (triangle_norms) delete[] triangle_norms;
}

void Mesh::read_obj_file(const char* filename) {
	int vertex_number = 0;
	int vertex_normal_number = 0;
	// Reset
	verts.clear();
	triangles.clear();
	if (triangle_norms) delete[] triangle_norms;
	vbo_ready = false;

	FILE *fp = fopen(filename, "r+");
	char token[2];
	unsigned int data[64];
	while(feof(fp)==0) {
		do { // Remove any trailing stuff from last line
			token[0] = fgetc(fp);
		} while (token[0] == '\n' || token[0] == '\r');
		token[1] = fgetc(fp);
		if(token[0]=='#') {
			int c;
			while(feof(fp)==0)
				if((c=fgetc(fp))=='\r' || c=='\n') break;
		} else if(token[0]=='v' && token[1]==' ') { //vertex
			if (vertex_number == verts.size()) {
				Vertex v;
				verts.push_back(v);
			}
			fscanf(fp, "%f %f %f\n",
			       &(verts[vertex_number].pos[0]),
			       &(verts[vertex_number].pos[1]),
			       &(verts[vertex_number].pos[2])
			      );
			vertex_number++;
		} else if(token[0]=='v' && token[1]=='t') {
			float temp[2];
			fscanf(fp, "%f %f\n", &temp[0], &temp[1]);
		} else if(token[0]=='v' && token[1]=='n') {
			if (vertex_normal_number == verts.size()) {
				Vertex v;
				verts.push_back(v);
			}
			fscanf(fp, "%f %f %f\n",
			       &(verts[vertex_normal_number].norm[0]),
			       &(verts[vertex_normal_number].norm[1]),
			       &(verts[vertex_normal_number].norm[2])
			      );
			vertex_normal_number++;
		} else if(token[0]=='f' && token[1]==' ') {
			int data_number=0;
			bool end = false;
			while(feof(fp)==0) {
				fscanf(fp, "%u", &data[data_number++]);
				while(feof(fp)==0) {
					char c=fgetc(fp);
					if(c == ' ' || c == '\t') break;
					if(c == '\n'|| c == '\r') {end=true; break;}
				}
				if(end) break;
			}
			for(int i=1; i<data_number-1; i++) {
				Triangle t;
				t.index[0] = data[0  ]-1;
				t.index[1] = data[i  ]-1;
				t.index[2] = data[i+1]-1;
				triangles.push_back(t);
			}
		}
	}
	/*printf("vert:%d norm:%d tri:%lu\n",
	       vertex_number,
	       vertex_normal_number,
	       triangles.size()
	      );*/
	fclose(fp);
}

void Mesh::rebuild_vertex_norms() {
	// Reset
	for (int i=0; i<verts.size(); i++) {
		verts[i].norm[0] = verts[i].norm[1] = verts[i].norm[2] = 0;
	}
	build_triangle_norms();

	int v0, v1, v2;
	for (int i=0; i<triangles.size(); i++) {
		v0 = triangles[i].index[0];
		v1 = triangles[i].index[1];
		v2 = triangles[i].index[2];
		verts[v0].norm[0] = triangle_norms[i*3+0];
		verts[v0].norm[1] = triangle_norms[i*3+1];
		verts[v0].norm[2] = triangle_norms[i*3+2];
		verts[v1].norm[0] = triangle_norms[i*3+0];
		verts[v1].norm[1] = triangle_norms[i*3+1];
		verts[v1].norm[2] = triangle_norms[i*3+2];
		verts[v2].norm[0] = triangle_norms[i*3+0];
		verts[v2].norm[1] = triangle_norms[i*3+1];
		verts[v2].norm[2] = triangle_norms[i*3+2];
	}

	for (int i=0; i<verts.size(); i++) {
		normalize(verts[i].norm);
	}
}

void Mesh::render(GLuint shader_program) {
	if (!vbo_ready) init_vbo();

	glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triVBO);

	GLuint c0=glGetAttribLocation(shader_program, "vertex_position");
	GLuint c1=glGetAttribLocation(shader_program, "vertex_normal");
	glEnableVertexAttribArray(c0);
	glEnableVertexAttribArray(c1);

	glVertexAttribPointer(c0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      reinterpret_cast<void*>(offsetof(Vertex, pos)));
	glVertexAttribPointer(c1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      reinterpret_cast<void*>(offsetof(Vertex, norm)));

	glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT,
	               reinterpret_cast<void*>(offsetof(Triangle, index)));
}

void Mesh::write_obj_file(const char* filename) {
	FILE *fp=fopen(filename, "w+");
	for (vector<Vertex>::iterator it = verts.begin(); it != verts.end(); it++) {
		fprintf(fp, "v %f %f %f\n", (*it).pos[0], (*it).pos[1], (*it).pos[2]);
		fprintf(fp, "vn %f %f %f\n", (*it).norm[0], (*it).norm[1],
		        (*it).norm[2]
		       );
	}
	for (vector<Triangle>::iterator it = triangles.begin();
	     it != triangles.end(); it++) {
		fprintf(fp, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
		        (*it).index[0]+1, (*it).index[0]+1, (*it).index[0]+1,
		        (*it).index[1]+1, (*it).index[1]+1, (*it).index[1]+1,
		        (*it).index[2]+1, (*it).index[2]+1, (*it).index[2]+1
		       );
	}
	fclose(fp);
}

}
