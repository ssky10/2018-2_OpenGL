#include <windows.h>
#include "opengl/glut.h"

void MyDisplay() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//glTranslatef(0.2, -0.2, 0.0);
	//glScalef(1.0, 0.5, 1.0);
	//glRotatef(10, 0, 0, 1);

	////1번
	//glScalef(0.5, 1.0, 1.0);

	////2번
	//glRotatef(45, 0, 0, 1);

	////3번
	//glTranslatef(0.5, 0.0, 0.0);
	//glRotatef(45, 0, 0, 1);

	////4번
	//glRotatef(45, 0, 0, 1);
	//glTranslatef(0.5, 0.0, 0.0);


	////5번
	//glRotatef(90, 1, 0, 0);
	//glutWireSphere(0.5, 10, 20);

	////6번
	//glTranslatef(0.75, 0.75, 0.0);
	//glScalef(0.25, 0.25, 0.25);
	//glRotatef(90, 1, 0, 0);	
	//glutWireSphere(0.5, 10, 20);

	//glLoadIdentity();

	//glTranslatef(0.5, 0.0, 0.0);
	//glScalef(0.5, 1.0, 1.0);

	//추가
	glScalef(0.5, 2.0, 1.0);
	glRotatef(90, 0.5, 0, 0);
	glutWireTeapot(0.6);

	/*glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.0, 0.5);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5, -0.5);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.5, -0.5);
	glEnd();*/

	glFlush();
}

int main() {
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Geometry Transform");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
