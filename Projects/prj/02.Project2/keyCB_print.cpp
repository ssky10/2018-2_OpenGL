#include <windows.h>
#include "opengl/glut.h"
#include <stdio.h>

GLfloat size = 0.3;
GLenum mode = GL_POLYGON;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(mode);
	glVertex3f(-size, -size, 0.0);
	glVertex3f(size, -size, 0.0);
	glVertex3f(size, size, 0.0);
	glVertex3f(-size, size, 0.0);
	glEnd();
	glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed)
	{
	case 'R':
	case 'r':
		glColor3f(1.0, 0.0, 0.0); break;
	case 'G':
	case 'g':
		glColor3f(0.0, 1.0, 0.0); break;
	case 'B':
	case 'b':
		glColor3f(0.0, 0.0, 1.0); break;
	case 'T':
	case 't':
		mode = GL_TRIANGLES; break;
	case '+':
		if (size < 0.9) size += 0.1;
		break;
	case '-':
		if (size > 0.2) size -= 0.1;
		break;
	case 'Q':
	case 'q':
	case 27:
		exit(0);	
	}
	char info[128];
	sprintf_s(info, "size = %.1f", size);
	glutSetWindowTitle(info);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("Keyboard Callback");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutKeyboardFunc(MyKeyboard);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}