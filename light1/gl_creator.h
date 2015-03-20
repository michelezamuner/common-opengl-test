#ifndef gl_creator_h
#define gl_creator_h

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void myDisplay ();
void myIdle ();
void myKeyboard (unsigned char, int, int);

float colors [5] [3] = {
	{0.0f, 0.0f, 0.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}
};

enum {black, white, red, green, blue};

//proprietà finestra
bool winSingle = false,
winDepth = true;

unsigned int displayMode () {
	unsigned int dM = GLUT_RGB;
	
	if (winSingle)
		dM |= GLUT_SINGLE;
	else
		dM |= GLUT_DOUBLE;

	if (winDepth)
		dM |= GLUT_DEPTH;

	return dM;
}

int winSize [] = {500, 500},
winPos [] = {100, 100};
unsigned int winBackColor = black;

const char* winName = "NewWindow";

//viewport&projection
int viewport [] = {0, 0, winSize [0], winSize [1]};
bool viewPerspective = true;
float viewMaxDimension = 1.0f,
viewZoom = 10.0f,
viewNearPlane = 1.0f,
viewFarPlane = 1000.0f;

//camera
float camPos [] = {20.0, 20.0, 20.0},
camTarget [] = {0.0, 0.0, 0.0},
camTop [] = {0.0, 0.0, 1.0};

//light
float light_ambient [] = {0.0, 0.0, 0.0, 1.0},
	light_diffuse [] = {0.7, 0.7, 0.7, 1.0},
	light_specular [] = {0.7, 0.7, 0.7, 1.0},
	light_position [] = {0.0, 200.0, 200.0},
	mat_ambient [] = {0.2, 0.1, 0.0, 1.0},
	mat_diffuse [] = {0.7, 0.3, 0.0, 1.0},
	mat_specular [] = {0.7, 0.3, 0.0, 1.0},
	mat_shininess [] = {1.0};

void display () {
	if (winDepth)
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear (GL_COLOR_BUFFER_BIT);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (camPos[0], camPos[1], camPos[2],
		camTarget[0], camTarget[1], camTarget[2],
		camTop[0], camTop[1], camTop[2]);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	myDisplay ();

	if (winSingle)
		glFlush ();
	else
		glutSwapBuffers ();
}

void reshape (int w, int h) {
	float r = (float)winSize[0] / (float)winSize[1],
		D = viewMaxDimension / viewZoom;

	winSize[0] = w; winSize[1] = h;
	viewport[2] = w; viewport[3] = h;

	glViewport (viewport[0], viewport[1], viewport[2], viewport[3]);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	if (viewPerspective)
		glFrustum (-w / viewZoom, w / viewZoom, -h / viewZoom, h / viewZoom,
			viewNearPlane, viewFarPlane);
	else
		glOrtho (-w / viewZoom, w / viewZoom, -h / viewZoom, h / viewZoom,
			viewNearPlane, viewFarPlane);
}

void idle () {
	myIdle ();
	glutPostRedisplay ();
}

void keyboard (unsigned char key, int x, int y) {
	myKeyboard (key, x, y);
	glutPostRedisplay ();
}

void runGl (int* argc, char** argv) {
	glutInit (argc, argv);
	glutInitDisplayMode (displayMode ());
	glutInitWindowSize (winSize[0], winSize[1]);
	glutInitWindowPosition (winPos[0], winPos[1]);
	glutCreateWindow (winName);

	glClearColor (colors [winBackColor] [0],
		colors [winBackColor] [1],
		colors [winBackColor] [2],
		0.0f
		);

	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutIdleFunc (idle);
	glutKeyboardFunc (keyboard);

	glutMainLoop ();
}

#endif
