#include <windows.h>
#include "opengl/glut.h"

void MyDisplay1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glutSolidTeapot(0.1);
	glTranslatef(0.2, 0.2, 0);
	glutSolidTeapot(0.1);
	glPushMatrix();
	glTranslatef(0.5, -0.1, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.5, 0.5, 0);
	glutSolidTeapot(0.1);
	glPopMatrix();
	glTranslatef(-0.8, 0.3, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(1.5, 1.5, 1.5);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(0.1);
	glPopMatrix();
	glTranslatef(0, -0.5, 0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidTeapot(0.1);

	glFlush();
}

int code0606() {
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Geometic Transform");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay1);
	glutMainLoop();
	return 0;
}