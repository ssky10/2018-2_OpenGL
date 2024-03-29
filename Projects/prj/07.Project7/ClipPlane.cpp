#include <Windows.h>
#include "opengl/glut.h"

int flag = 0;

void MyDisplay2() {
	GLdouble eqn1[4] = { 0.0,1.0,0.0,0.0 };
	GLdouble eqn1_1[4] = { 0.0,1.0,0.0,0.5 };
	GLdouble eqn2[4] = { -1.0,0.0,0.0,0.0 };
	GLdouble eqn2_1[4] = { -1.0,0.0,0.0,0.5 };
	GLdouble eqn3[4] = { 0.0,0.0,-1.0,0.0 };
	GLdouble eqn3_1[4] = { 0.0,0.0,-1.0,0.5 };
	GLdouble eqn4[4] = { 1.0,1.0,0.0,0.0 };
	GLdouble eqn5[4] = { 1.0,0.0,0.0,0.5 };
	GLdouble eqn6[4] = { 1.0,0.0,-1.0,0.0 };
	GLdouble eqn6_1[4] = { 1.0,0.0,-1.0,0.5 };

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.0, 1.0, 0.0);

	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);

	
	if (flag == 0) {
		glutSetWindowTitle("Clip Lower half -- z > 0");
		glClipPlane(GL_CLIP_PLANE0, eqn3);
		glEnable(GL_CLIP_PLANE0);
	}
	else if (flag == 1) {
		glutSetWindowTitle("Clip Lower half -- x > 0");
		glClipPlane(GL_CLIP_PLANE0, eqn2);
		glEnable(GL_CLIP_PLANE0);
	}
	else if (flag == 2) {
		glutSetWindowTitle("Clip Lower half -- x-z < 0");
		glClipPlane(GL_CLIP_PLANE0, eqn6);
		glEnable(GL_CLIP_PLANE0);
	}
	else if (flag == 3) {
		glutSetWindowTitle("Clip Lower half -- ( z > 0 ) & ( x > 0 )");
		glClipPlane(GL_CLIP_PLANE0, eqn3);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn2);
		glEnable(GL_CLIP_PLANE1);
	}
	else if (flag == 4) {
		glutSetWindowTitle("Clip Lower half -- ( z > 0 ) & ( x-z < 0 )");
		glClipPlane(GL_CLIP_PLANE0, eqn3);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn6);
		glEnable(GL_CLIP_PLANE1);
	}
	else if (flag == 5) {
		glutSetWindowTitle("Clip Lower half -- ( y < 0 ) & ( x-z < 0 )");
		glClipPlane(GL_CLIP_PLANE0, eqn1);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn6);
		glEnable(GL_CLIP_PLANE1);
	}
	else if (flag == 6) {
		glutSetWindowTitle("Clip Lower half -- ( z > 0.5 ) & ( x-z < 0 )");
		glClipPlane(GL_CLIP_PLANE0, eqn3_1);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn2_1);
		glEnable(GL_CLIP_PLANE1);
	}
	else if (flag == 7) {
		glutSetWindowTitle("Clip Lower half -- ( z > 0.5 ) / ( x-z < 0.5 )");
		glClipPlane(GL_CLIP_PLANE0, eqn3_1);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn6_1);
		glEnable(GL_CLIP_PLANE1);
	}
	else if (flag == 8) {
		glutSetWindowTitle("Clip Lower half -- ( y < 0.5 ) / ( x-z < 0.5 )");
		glClipPlane(GL_CLIP_PLANE0, eqn1_1);
		glEnable(GL_CLIP_PLANE0);
		glClipPlane(GL_CLIP_PLANE1, eqn6_1);
		glEnable(GL_CLIP_PLANE1);
	}

	glutWireSphere(1.0, 20, 16);
	glFlush();
}

void MySpecialKeyboard2(int KeyPressed, int X, int Y) {
	switch (KeyPressed)
	{
	case GLUT_KEY_RIGHT:
		if (flag < 8)flag++;
		else flag = 0;
		break;
	case GLUT_KEY_LEFT:
		if (flag > 0)flag--;
		else flag = 8;
		break;
	}
	glutPostRedisplay();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
}

int ClipPlane() {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Clip Plane");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(MyDisplay2);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MySpecialKeyboard2);
	glutMainLoop();
	return 0;
}