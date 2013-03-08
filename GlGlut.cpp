#include "GlGlut.h"

using namespace std;

namespace lab3 {

// Use to get transpose of inverse of upper 3x3 from modelview
void matrix_inverse_3x3(float in[4][4], float out[3][3]) {
	float det = in[0][0] * (in[1][1] * in[2][2] - in[1][2] * in[2][1])
	          + in[0][1] * (in[1][2] * in[2][0] - in[2][2] * in[1][0])
	          + in[0][2] * (in[1][0] * in[2][1] - in[1][1] * in[2][0]);
	float invdet = 1.0/det;

	out[0][0] = (in[1][1] * in[2][2] - in[1][2] * in[2][1]) * invdet;
	out[0][1] = (in[1][2] * in[2][0] - in[1][0] * in[2][2]) * invdet;
	out[0][2] = (in[1][0] * in[2][1] - in[1][1] * in[2][0]) * invdet;
	out[1][0] = (in[0][2] * in[2][1] - in[0][1] * in[2][2]) * invdet;
	out[1][1] = (in[0][0] * in[2][2] - in[0][2] * in[2][0]) * invdet;
	out[1][2] = (in[0][1] * in[2][0] - in[0][0] * in[2][1]) * invdet;
	out[2][0] = (in[0][1] * in[1][2] - in[0][2] * in[1][1]) * invdet;
	out[2][1] = (in[0][2] * in[1][0] - in[0][0] * in[1][2]) * invdet;
	out[2][2] = (in[0][0] * in[1][1] - in[0][1] * in[1][0]) * invdet;
}

void matrix_multiply_point(float m[4][4], float v[4], float r[4]) {
	r[0] = r[1] = r[2] = r[3] = 0.0f;
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
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

	float projection[4][4];
	Matrix_Perpsective(60.0, 1.0, 0.1, 100, projection);

	float modelview[4][4];
	Matrix_LookAt(0, 0, 5, 0, 0, 0, 0, 1, 0, modelview);

	float temp[4][4];
	Matrix_Translate(0.0, -1.0, 0.0, temp);
	Matrix_Multiplication(modelview, temp, modelview);
	Matrix_Rotate(x_angle, 0, 1, 0, temp);
	Matrix_Multiplication(modelview, temp, modelview);
	Matrix_Rotate(y_angle, 1, 0, 0, temp);
	Matrix_Multiplication(modelview, temp, modelview);
	Matrix_Scale(scale_size, scale_size, scale_size, temp);
	Matrix_Multiplication(modelview, temp, modelview);

	// Normal matrix is transpose of inverse of modelview's upper left 3x3
	float normal[3][3];
	matrix_inverse_3x3(modelview, normal);

	float modelview_projection[4][4];
	Matrix_Multiplication(projection, modelview, modelview_projection);

	GLuint m = glGetUniformLocation(programObject, "m_modelview");
	GLuint p = glGetUniformLocation(programObject, "m_mvp");
	GLuint n = glGetUniformLocation(programObject, "m_normal");

	// Send with transpose=true to convert to opengl's column major
	glUniformMatrix4fv(m, 1, GL_TRUE, &modelview[0][0]);
	glUniformMatrix4fv(p, 1, GL_TRUE, &modelview_projection[0][0]);
	glUniformMatrix3fv(n, 1, GL_TRUE, &normal[0][0]);

	if (programObject == phong_point) {
		float light_pos_loc[4] = {1.0, -1.0, 1.0, 1.0};
		float (*light_pos)[4] = &light_pos_loc;
		if (phong_fixed_point) {
			// Multiply light's position by model view matrix to keep it
			// fixed with respect to mesh object
			float light_pos_mv[4];
			matrix_multiply_point(modelview, light_pos_loc, light_pos_mv);
			light_pos = &light_pos_mv;
		}
		GLuint l = glGetUniformLocation(programObject, "light_pos");
		glUniform4fv(l, 1, *light_pos);
	}

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
			programObject = phong_point;
			phong_fixed_point = false;
			break;
		case '2':
			programObject = checkerboard;
			break;
		case '3':
			programObject = wood;
			break;
		case '4':
			programObject = phong_point;
			phong_fixed_point = true;
			break;
		case '5':
			programObject = phong_dir;
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
	phong_fixed_point = false;
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

	// Shaders
	Check_GPU_Status();
	printf("Loading shader phong_directional...\n");
	phong_dir = Setup_GLSL("phong_directional");
	printf("Loading shader phong_point...\n");
	phong_point = Setup_GLSL("phong_point");
	printf("Loading shader checkerboard...\n");
	checkerboard = Setup_GLSL("checkerboard");
	printf("Loading shader wood...\n");
	wood = Setup_GLSL("wood");
	programObject = phong_point;

	// Start
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}

} // namespace lab3
