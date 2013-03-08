#include "GlGlut.h"

using namespace std;

namespace lab3 {

const GLfloat GlGlut::ambient[4] = {0.2, 0.2, 0.2, 1.0};
const GLfloat GlGlut::light0Position[4] = {0.0, 0.15, 5.0, 1.0};
const GLfloat GlGlut::ambient0[4] = {0.0, 0.0, 0.0, 1.0};
const GLfloat GlGlut::diffuse0[4] = {0.8, 0.8, 0.8, 1.0};
const GLfloat GlGlut::specular0[4] = {0.8, 0.8, 0.8, 1.0};
const GLfloat GlGlut::spotDir0[3] = {0.0, 0.0, -1.0};

// Use to get transpose of inverse of upper 3x3 from modelview
void matrix_transpose_inverse_3x3(float in[4][4], float out[3][3]) {
	float invdet = 1.0f/(in[0][0]*(in[1][1]*in[2][2]-in[2][1]*in[1][2])
	                    -in[0][1]*(in[1][0]*in[2][2]-in[1][2]*in[2][0])
	                    +in[0][2]*(in[1][0]*in[2][1]-in[1][1]*in[2][0]));
	out[0][0] = (in[1][1]*in[2][2]-in[2][1]*in[1][2])*invdet;
	out[1][0] = (in[0][1]*in[2][2]-in[0][2]*in[2][1])*invdet;
	out[2][0] = (in[0][1]*in[1][2]-in[0][2]*in[1][1])*invdet;
	out[0][1] = -1*(in[1][0]*in[2][2]-in[1][2]*in[2][0])*invdet;
	out[1][1] = (in[0][0]*in[2][2]-in[0][2]*in[2][0])*invdet;
	out[2][1] = -1*(in[0][0]*in[1][2]-in[1][0]*in[0][2])*invdet;
	out[0][2] = (in[1][0]*in[2][1]-in[2][0]*in[1][1])*invdet;
	out[1][2] = -1*(in[0][0]*in[2][1]-in[2][0]*in[0][1])*invdet;
	out[2][2] = (in[0][0]*in[1][1]-in[1][0]*in[0][1])*invdet;
}

float normalize_4d(float v[4]) {
	float m = sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
	if(m<1e-14f) return m;
	v[0] /= m;
	v[1] /= m;
	v[2] /= m;
	v[3] /= m;
	return m;
}

void matrix_multiply_point(float m[4][4], float v[4], float r[4]) {
	r[0] = r[1] = r[2] = r[3] = 0.0f;
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			r[i] += m[i][j] * v[j];
		}
	}
}

void matrix3d_multiply_point(float m[3][3], float v[3], float r[3]) {
	r[0] = r[1] = r[2] = 0.0f;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			r[i] += m[i][j] * v[j];
		}
	}
}

GlGlut *GlGlut::instance = NULL;

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(programObject);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, .1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,5,0,0,0,0,1,0);

	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir0);

	glRotatef(x_angle, 0, 1,0);
	glRotatef(y_angle, 1,0,0);
	glScalef(scale_size, scale_size, scale_size);

	/*float projection[4][4];
	Matrix_Perpsective(60.0, 1.0, 0.1, 100, projection);

	float modelview[4][4];
	Matrix_LookAt(0, 0, 5, 0, 0, 0, 0, 1, 0, modelview);*/

////////////////
	// Light direction in world space
	/*float light_dir_w[4] = {1.0f, 1.0f, 1.0f, 0.0f};
	float light_dir_c[4];
	matrix_multiply_point(modelview, light_dir_w, light_dir_c);
	// Light direction in camera space
	normalize_4d(light_dir_c);
	printf("l: %f %f %f %f\n", light_dir_c[0], light_dir_c[1], light_dir_c[2],
	        light_dir_c[3]);*/
////////////////
	

	/*float temp[4][4];
	Matrix_Rotate(x_angle, 0, 1, 0, temp);
	Matrix_Multiplication(modelview, temp, modelview);
	Matrix_Rotate(y_angle, 1, 0, 0, temp);
	Matrix_Multiplication(modelview, temp, modelview);
	Matrix_Scale(scale_size, scale_size, scale_size, temp);
	Matrix_Multiplication(modelview, temp, modelview);

	// Normal matrix is transpose of inverse of modelview's upper left 3x3
	float normal[3][3];
	matrix_transpose_inverse_3x3(modelview, normal);*/

/////////////////////
	/*printf("m_mv: %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
	       modelview[0][0], modelview[0][1], modelview[0][2], modelview[0][3],
	       modelview[1][0], modelview[1][1], modelview[1][2], modelview[1][3],
	       modelview[2][0], modelview[2][1], modelview[2][2], modelview[2][3],
	       modelview[3][0], modelview[3][1], modelview[3][2], modelview[3][3]);
	printf("m_n: %f %f %f\n%f %f %f\n%f %f %f\n",
	       normal[0][0], normal[0][1], normal[0][2],
	       normal[1][0], normal[1][1], normal[1][2],
	       normal[2][0], normal[2][1], normal[2][2]);

	float *tv_tmp = mesh->verts[10000].pos;
	float tv[4] = {tv_tmp[0], tv_tmp[1], tv_tmp[2], 1.0f};
	printf("tv: %f %f %f %f\n", tv[0], tv[1], tv[2], tv[3]);
	float eye[4];
	matrix_multiply_point(modelview, tv, eye);
	eye[0] *= -1;
	eye[1] *= -1;
	eye[2] *= -1;
	printf("eye: %f %f %f\n", eye[0], eye[1], eye[2]);

	float *tn = mesh->verts[10000].norm;
	printf("tn: %f %f %f\n", tn[0], tn[1], tn[2]);
	float tnn[3];
	matrix3d_multiply_point(normal, tn, tnn);
	printf("tnn: %f %f %f\n", tnn[0], tnn[1], tnn[2]);

	float intentsity = light_dir_c[0]*tnn[0]+light_dir_c[1]*tnn[1]
	                      +light_dir_c[2]*tnn[2];
	printf("int: %f\n", intentsity);

	float half[3];
	half[0] = light_dir_c[0]+eye[0];
	half[1] = light_dir_c[1]+eye[1];
	half[2] = light_dir_c[2]+eye[2];
	Normalize_3D(half);
	printf("half: %f %f %f\n", half[0], half[1], half[2]);*/
//////////////////


	/*float modelview_projection[4][4];
	Matrix_Multiplication(projection, modelview, modelview_projection);

	GLuint m = glGetUniformLocation(programObject, "m_mv");
	GLuint p = glGetUniformLocation(programObject, "m_mvp");
	GLuint n = glGetUniformLocation(programObject, "m_normal");
	//GLuint l = glGetUniformLocation(programObject, "l_dir");

	//glUniform3fv(l, 1, light_dir_c);
	// Send with transpose=true to convert to opengl's column major
	glUniformMatrix4fv(m, 1, GL_TRUE, &modelview[0][0]);
	glUniformMatrix4fv(p, 1, GL_TRUE, &modelview_projection[0][0]);
	glUniformMatrix4fv(n, 1, GL_FALSE, &normal[0][0]);*/

	mesh->render(programObject);

	glutSwapBuffers();
}

void GlGlut::idle() {

}

void GlGlut::keyboard(unsigned char key, int mousex, int mousey) {
	switch(key) {
		case 3:  // Ctrl-c
		case 27: // Esc
			exit(EXIT_SUCCESS);
			break;
		case '1':
			
			break;
		case '2':
			
			break;
		case '3':
			
			break;
		case '4':
			
			break;
		default:
			//cout << "unused key: " << (int) key << endl;
			return;
	}
	glutPostRedisplay();
}

void GlGlut::mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		press_x = x;
		press_y = y;
		if (button == GLUT_LEFT_BUTTON)
			xform_mode = XFORM_ROTATE;
		else if (button == GLUT_RIGHT_BUTTON)
			xform_mode = XFORM_SCALE;
	} else if (state == GLUT_UP)
		xform_mode = XFORM_NONE;
}

void GlGlut::mouseMotion(int x, int y) {
	if (xform_mode==XFORM_ROTATE) {
		x_angle += (x - press_x)/5.0;
		if (x_angle > 180) x_angle -= 360;
		else if (x_angle <-180) x_angle += 360;
		press_x = x;

		y_angle += (y - press_y)/5.0;
		if (y_angle > 180) y_angle -= 360;
		else if (y_angle <-180) y_angle += 360;
		press_y = y;
    } else if (xform_mode == XFORM_SCALE) {
		float old_size = scale_size;
		scale_size *= (1+ (y - press_y)/60.0);
		if (scale_size <0) scale_size = old_size;
		press_y = y;
    }
    glutPostRedisplay();
}

void GlGlut::reshape(int w, int h) {
	screen_width = w;
	screen_height = h;

	if (w > h) {
		glViewport((w-h)/2, 0, h, h);
	} else {
		glViewport(0, (h-w)/2, w, w);
	}

	glutPostRedisplay();
}
/////////////////////////

//// Static wrappers ////
void GlGlut::displayWrapper() {
	instance->display();
}

void GlGlut::idleWrapper() {
	instance->idle();
}

void GlGlut::keyboardWrapper(unsigned char key, int mousex, int mousey) {
	instance->keyboard(key, mousex, mousey);
}

void GlGlut::mouseClickWrapper(int button, int state, int x, int y) {
	instance->mouseClick(button, state, x, y);
}

void GlGlut::mouseMotionWrapper(int x, int y) {
	instance->mouseMotion(x, y);
}

void GlGlut::reshapeWrapper(int w, int h) {
	instance->reshape(w, h);
}
/////////////////////////

GlGlut::GlGlut() {
	screen_width = DEF_SCREEN_W;
	screen_height = DEF_SCREEN_H;
	xform_mode = XFORM_NONE;
	x_angle = 0.0f;
	y_angle = 0.0f;
	scale_size = 1.0f;

	light0 = true;
}

GlGlut::~GlGlut() {
	// Nothing to do here
}

void GlGlut::setInstance() {
	instance = this;
}

void GlGlut::start(int *argc, char *argv[]) {
	setInstance();

	// Init glut
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(WINDOW_TITLE);

	// Register callbacks
	glutDisplayFunc(displayWrapper);
	glutKeyboardFunc(keyboardWrapper);
	glutMouseFunc(mouseClickWrapper);
	glutMotionFunc(mouseMotionWrapper);
	glutReshapeFunc(reshapeWrapper);

	// glew?
#ifdef _WIN32
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		cerr << "Fatal Error: " << glewGetErrorString(err) << endl;
		exit(1);
	}
#endif

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);

	// Turn on culling
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Setup
	mesh = new Mesh();
	mesh->read_obj_file("bunny.mesh");
	mesh->rebuild_vertex_norms();

	// Lights
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	// Shaders
	programObject = Setup_GLSL("shader");

	// Start
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}

} // namespace lab3
