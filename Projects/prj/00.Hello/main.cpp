#include <windows.h>
#include "opengl/glut.h"

void DoDisplay() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Hello, OpenGL");
	glutDisplayFunc(DoDisplay);
	glutMainLoop();
	return 0;
}