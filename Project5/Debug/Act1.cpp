//
//  Main.cpp
//

#include <cassert>
#include <cmath>
#include <string>
#include <iostream>
#include "glut.h"
#include "GetGlut.h"
#include "Sleep.h"

using namespace std;

void init();
void initDisplay();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void update();
void display();



int main(int argc, char* argv[])
{
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Fourth OpenGL Program");
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 1;
}

void init()
{
	initDisplay();
}

void initDisplay()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void update()
{
	//update your variables here
	
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(2.0, 3.0, 4.0,
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);

	// display positive X, Y, and Z axes near origin
	glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(2.0, 0.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 2.0, 0.0);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	// draw a purple wireframe cube
	glColor3d(1.0, 0.0, 1.0);
	glPushMatrix();
		glTranslated(0.0, 0.0, 0.0);
		glRotated(45, 0.0, 1.0, 0.0);
		glScaled(1.0, 1.0, 1.0);
		glutWireCube(1.0);
	glPopMatrix();

	glutSwapBuffers();
}
