#include <Windows.h>
#include "opengl/glut.h"
#include <math.h>

void MyDisplay() {
	GLint scaleFactor = 1;
	GLushort pattern[] = { 0xfff3, 0x5fff, 0x57ff, 0x574b, 0x7abd };
	GLfloat height = -0.9;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);

	glEnable(GL_LINE_STIPPLE);
	for (int i = 0; i < 5; i++) {
		glLineStipple(3, pattern[i]);
		glBegin(GL_LINES);
		glVertex3f(-1.0, height, 0.0);
		glVertex3f(1.0, height, 0.0);
		glEnd();
		height += 0.4;
	}
	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

int DrawLine() {
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_SINGLE);
	glutCreateWindow("Draw Point");

	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}