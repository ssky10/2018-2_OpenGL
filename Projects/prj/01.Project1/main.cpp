#include <windows.h>
#include "opengl/glut.h"

void DoDisplay() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.3, -0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Hello, OpenGL");
	glutDisplayFunc(DoDisplay);
	glutMainLoop();
	return 0;
}