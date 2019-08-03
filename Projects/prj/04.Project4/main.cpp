#include <Windows.h>
#include "opengl/glut.h"
#include <stdio.h>

int flag = 0;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5,0.4,0.3,1.0 };
	GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_ambient[] = { 0.5,0.4,0.3,1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };
	GLfloat light_position[] = { -3,6,3.0,0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (flag)
	{
	case 0: gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); break;
	case 1: gluLookAt(-0.5, 0.0, 0.0, -0.5, 0.0, -1.0, 0.0, 1.0, 0.0); break;
	case 2: gluLookAt(0.5, 0.0, 0.0, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0); break;
	case 3: gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0); break;
	case 4: gluLookAt(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0); break;
	case 5: gluLookAt(0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0); break;
	case 6: gluLookAt(0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0); break;
	case 7: gluLookAt(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0); break;
	case 8: gluLookAt(0.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 1.0, 0.0); break;
	case 9: gluLookAt(0.0, 0.0, 0.0, -1.0, -1.0, 1.0, 0.0, 1.0, 0.0); break;
	case 10: gluLookAt(0.0, 0.0, 0.0, 1.0, -1.0, -1.0, 0.0, 1.0, 0.0); break;
	case 11: gluLookAt(0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 1.0, 0.0); break;
	default:
		break;
	}
	char title[162];
	sprintf_s(title, "%d번 그림", flag + 1);
	glutSetWindowTitle(title);
	////1번
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	////2번
	//gluLookAt(-0.5, 0.0, 0.0, -0.5, 0.0, -1.0, 0.0, 1.0, 0.0);

	////3번
	//gluLookAt(0.5, 0.0, 0.0, 0.5, 0.0, -1.0, 0.0, 1.0, 0.0);

	////4번
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	////5번
	//gluLookAt(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	////6번
	//gluLookAt(0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	////7번
	//gluLookAt(0.0, 0.0, 0.0, 0.0, -70.0, -1.0, 0.0, 1.0, 0.0);

	////8번
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 70.0, -1.0, 0.0, 1.0, 0.0);

	////9번
	//gluLookAt(0.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, 1.0, 0.0);

	////10번
	//gluLookAt(0.0, 0.0, 0.0, -1.0, -1.0, 1.0, 0.0, 1.0, 0.0);

	////11번
	//gluLookAt(0.0, 0.0, 0.0, 1.0, -1.0, -1.0, 0.0, 1.0, 0.0);

	//12번
	//gluLookAt(0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 1.0, 0.0);

	glutSolidTeapot(0.5);
	glFlush();
}

void MySpecialKeyboard(int KeyPressed, int X, int Y) {
	switch (KeyPressed)
	{
	case GLUT_KEY_RIGHT:
		if (flag < 11)flag++;
		else flag = 0;
		break;
	case GLUT_KEY_LEFT:
		if (flag > 0)flag--;
		else flag = 11;
		break;
	}
	glutPostRedisplay();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("View Coordinate Transform");
	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecialKeyboard);
	glutMainLoop();
	return 0;
}