#include <Windows.h>
#include <stdio.h>
#include "opengl/glut.h"

int cullface = 0;
int on_off = 0;

void MyDisplay1() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, -0.3, -0.3, -1.0, 0.0, 1.0, 0.0);

	if (on_off == 1) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);  //default 반시계방향이 전면
	if (cullface == 0) glCullFace(GL_BACK);  //default 후면제거
	else if (cullface == 1) glCullFace(GL_FRONT);
	else if (cullface == 2) glCullFace(GL_FRONT_AND_BACK);

	glPolygonMode(GL_FRONT, GL_FILL);  //default GL_FILL
	glPolygonMode(GL_BACK, GL_LINE);

	//F
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.3, -0.6);
	glVertex3f(-0.5, 0.3, -0.6);
	glVertex3f(0.5, 0.3, -0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glEnd();

	//E
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.3, 0.6);
	glVertex3f(-0.5, 0.3, 0.6);
	glVertex3f(-0.5, 0.3, -0.6);
	glVertex3f(-0.5, -0.3, -0.6);
	glEnd();
	
	//D
	glColor3f(0.0, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -0.3, -0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glVertex3f(0.5, -0.3, 0.6);
	glVertex3f(-0.5, -0.3, 0.6);
	glEnd();

	//C
	glColor3f(0.5, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.3, -0.6);
	glVertex3f(-0.5, 0.3, 0.6);
	glVertex3f(0.5, 0.3, 0.6);
	glVertex3f(0.5, 0.3, -0.6);
	glEnd();

	//B
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, -0.3, 0.6);
	glVertex3f(0.5, -0.3, -0.6);
	glVertex3f(0.5, 0.3, -0.6);
	glVertex3f(0.5, 0.3, 0.6);
	glEnd();

	////A
	//glColor3f(0.5, 0.0, 0.0);
	//glBegin(GL_POLYGON);
	//glVertex3f(-0.5, -0.3, 0.6);
	//glVertex3f(0.5, -0.3, 0.6);
	//glVertex3f(0.5, 0.3, 0.6);
	//glVertex3f(-0.5, 0.3, 0.6);
	//glEnd();
	
	glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed)
	{
	case 'o':
	case 'O':
		on_off = (on_off + 1) % 2;
		break;

	case 'c':
	case 'C':
		cullface = (cullface + 1) % 3;
		break;
	}
	char info[128];
	sprintf_s(info, "GL_CULL_FACE = %s / glCullFace(%s)", (on_off==1)?"on":"off", (cullface == 0)? "GL_BACK":(cullface == 1)? "GL_FRONT":"GL_FRONT_AND_BACK");
	glutSetWindowTitle(info);
	glutPostRedisplay();
}

int CullFace() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Back-Facing Removal");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutKeyboardFunc(MyKeyboard);
	glutDisplayFunc(MyDisplay1);
	glutMainLoop();
	return 0;
}