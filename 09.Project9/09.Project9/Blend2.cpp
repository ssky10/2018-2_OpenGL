#include <Windows.h>
#include <glut.h>

GLfloat Alpha = 0.3f;
GLenum Src = GL_SRC_ALPHA;
GLenum Dest = GL_ONE_MINUS_SRC_ALPHA;

void DoDisplay() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(Src,Dest);

	glColor4f(0, 0, 1, 0.9);
	glRectf(-0.5, 0.8, 0.5, 0.0);

	glColor4f(1, 0, 0, Alpha);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();
}

void DoMenu(int value) {
	switch (value)
	{
	case 1:
		Src = GL_ONE;
		Dest = GL_ZERO;
		break;
	case 2:
		Src = GL_SRC_ALPHA;
		Dest = GL_ONE_MINUS_SRC_ALPHA;
		break;
	}
	glutPostRedisplay();
}

void DoKeyboard(unsigned char ch, int x, int y) {
	switch (ch)
	{
	case 'u':
		if(Alpha < 1) Alpha += 0.1f;
		break;
	case 'd':
		if (Alpha > 0) Alpha -= 0.1f;
		break;
	}
	glutPostRedisplay();
}

int main() {
	glutCreateWindow("OpenGL");
	glutDisplayFunc(DoDisplay);
	glutKeyboardFunc(DoKeyboard);
	glutCreateMenu(DoMenu);
	glutAddMenuEntry("Opaque", 1);
	glutAddMenuEntry("Translucent", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}