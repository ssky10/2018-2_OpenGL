#include <Windows.h>
#include "opengl/glut.h"

void MyDisplay2() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.3, 0.3, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(0.3);

	glTranslatef(-0.6, 0.0, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(0.5);

	glTranslatef(0.3, 0.2, 0.8);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.5);

	glFlush();
}

int HiddenRemoval2() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Back-Faceing Removal");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay2);
	glutMainLoop();
	return 0;
}