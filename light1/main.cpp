#include "gl_creator.h"
#include <math.h>

#define PI 3.141592653589793

double light_dist = 0.5, light_long = 30, light_lat = 20,
cam_dist = 10.0, cam_long = 45, cam_lat = 45;

void drawCylinder (double radius, double h, int slices, int stacks) {
	double dAlpha = 360 / slices, dH = h / stacks,
		alpha = 0, H = 0;

	for (int i = 1; i <= stacks; i++) {
		for (int j = 1; j <= slices; j++) {
			double x1 = radius*cos (alpha), x2 = radius*cos (alpha+dAlpha),
				y1 = radius*sin (alpha), y2 = radius*sin (alpha+dAlpha);

			glBegin (GL_POLYGON);
				glNormal3f (x1,y1,H);
				glVertex3f (x1,y1,H);
				glNormal3f (x2,y2,H);
				glVertex3f (x2,y2,H);
				glNormal3f (x2,y2,H+dH);
				glVertex3f (x2,y2,H+dH);
				glNormal3f (x1,y1,H+dH);
				glVertex3f (x1,y1,H+dH);
			glEnd ();

			alpha += dAlpha;
		}
		H += dH;
	}
}

void drawAxis () {
	float
		x_ambient [] = {0.2, 0.0, 0.0, 0.0},
		x_diffuse [] = {0.7, 0.0, 0.0, 0.0},
		x_specular [] = {0.7, 0.0, 0.0, 0.0},
		x_shininess [] = {50.0},
		y_ambient [] = {0.0, 0.2, 0.0, 0.0},
		y_diffuse [] = {0.0, 0.7, 0.0, 0.0},
		y_specular [] = {0.0, 0.7, 0.0, 0.0},
		y_shininess [] = {50.0},
		z_ambient [] = {0.0, 0.0, 0.2, 0.0},
		z_diffuse [] = {0.0, 0.0, 0.7, 0.0},
		z_specular [] = {0.0, 0.0, 0.7, 0.0},
		z_shininess [] = {50.0};

	glMaterialfv (GL_FRONT, GL_AMBIENT, x_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, x_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, x_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, x_shininess);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
		glRotatef (90.0f, 0.0f, 1.0f, 0.0f);
		drawCylinder (0.1f, 2.0f, 20.0f, 20.0f);
		glTranslatef (0.0f, 0.0f, 2.0f);
		glutSolidCone (0.3f, 0.6f, 20.0f, 20.0f);
	glPopMatrix ();

	glMaterialfv (GL_FRONT, GL_AMBIENT, y_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, y_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, y_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, y_shininess);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
		glRotatef (90.0f, -1.0f, 0.0f, 0.0f);
		drawCylinder (0.1f, 2.0f, 20.0f, 20.0f);
		glTranslatef (0.0f, 0.0f, 2.0f);
		glutSolidCone (0.3f, 0.6f, 20.0f, 20.0f);
	glPopMatrix ();

	glMaterialfv (GL_FRONT, GL_AMBIENT, z_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, z_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, z_specular);
	glMaterialfv (GL_FRONT, GL_SHININESS, z_shininess);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
		drawCylinder (0.1f, 2.0f, 20.0f, 20.0f);
		glTranslatef (0.0f, 0.0f, 2.0f);
		glutSolidCone (0.3f, 0.6f, 20.0f, 20.0f);
	glPopMatrix ();
	
}

void drawSphere (float radius = 0.3f) {
	float mat_ambient [] = {0.2, 0.1, 0.0, 1.0},
	mat_diffuse [] = {0.7, 0.3, 0.0, 1.0},
	mat_specular [] = {0.7, 0.3, 0.0, 1.0},
	mat_shininess [] = {1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glutSolidSphere (radius, 20, 20);
}

void myDisplay () {

	camPos[0] = cam_dist*cos (cam_lat)*cos (cam_long);
	camPos[1] = cam_dist*cos (cam_lat)*sin (cam_long);
	camPos[2] = cam_dist*sin (cam_lat);

	light_position[0] = light_dist*cos (light_lat)*cos (light_long);
	light_position[1] = light_dist*cos (light_lat)*sin (light_long);
	light_position[2] = light_dist*sin (light_lat);
	
	drawSphere ();

	drawAxis ();

	glDisable (GL_LIGHTING);
	glColor3f (1.0, 1.0, 1.0);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glTranslatef (light_position[0], light_position[1], light_position[2]);
	glutWireSphere (0.1f, 20.0f, 20.0f);
	glPopMatrix ();
	glEnable (GL_LIGHTING);
}

void myIdle () {
	light_long += 0.1;
}

void myKeyboard (unsigned char key, int x, int y) {
	switch (key) {
	case 'r': cam_dist -= 0.1; break;
	case 'f': cam_dist += 0.1; break;
	case 'w': cam_lat += 0.1; break;
	case 's': cam_lat -= 0.1; break;
	case 'a': cam_long -= 0.1; break;
	case 'd': cam_long += 0.1; break;
	case 'i': light_lat += 0.1; break;
	case 'k': light_lat -= 0.1; break;
	case 'o': light_dist -= 0.1; break;
	case 'l': light_dist += 0.1; break;
	}
}

int main (int argc, char** argv) {
	
	viewZoom = 700;

	camPos[0] = cam_dist*cos (cam_lat)*cos (cam_long);
	camPos[1] = cam_dist*cos (cam_lat)*sin (cam_long);
	camPos[2] = cam_dist*sin (cam_lat);

	light_position[0] = light_dist*cos (light_lat)*cos (light_long);
	light_position[1] = light_dist*cos (light_lat)*sin (light_long);
	light_position[2] = light_dist*sin (light_lat);

	runGl (&argc, argv);

	return 0;
}
