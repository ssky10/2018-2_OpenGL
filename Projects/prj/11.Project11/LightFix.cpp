#include <windows.h>
#include "opengl/glut.h"
#include <stdio.h>

GLfloat T = 0, R = 0, Px = 0.0;

void MyLightInit() {
	GLfloat light_ambient[] = { 1.0,0.0,0.0,1.0 };  //la:ÁÖº¯±¤ Æ¯¼º
	GLfloat light_diffuse[] = { 1.0,0.0,0.0,1.0 };  //ld:È®»ê±¤ Æ¯¼º
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 }; //ls:°æ¸é±¤ Æ¯¼º

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
}

void MyMaterialInit() {
	GLfloat material_ambient[] = { 0.1,0.1,0.1,1.0 }; //Ka:ÁÖº¯±¤ °è¼ö
	GLfloat material_diffuse[] = { 0.8,0.8,0.8,1.0 }; //Kd:È®»ê±¤ °è¼ö
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 }; //Ks:°æ¸é±¤ °è¼ö
	GLfloat material_shiniess[] = { 5.0 }; //n:±¤ÅÃ °è¼ö

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shiniess);
}

void MyReshape(int w, int h) {
	if (w < h)
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	else
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

void DoKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 't': T += 1; break;
	case 'g': T -= 1; break;

	case 'r': R += 10; break;
	case 'f': R -= 10; break;

	case 'p': Px += 0.2; break;
	case 'o': Px -= 0.2; break;

	case 'i':
		T = 0, R = 0, Px = 0; break;
	}
	char info[128];
	sprintf_s(info, "T=(%.1f), R=(%.1f), Lookat_Px=(%.1f)", T, R, Px);
	glutSetWindowTitle(info);
	MyLightInit();
	MyMaterialInit();
	glutPostRedisplay();
}

void DoDisplay_Fix() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(Px, 0, 0, 0, 0, -1, 0, 1, 0);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light0_position[] = { 0.0,5.0,5.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat spot_direction[] = { 0.0, 5.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

	glPushMatrix();
	glTranslatef(0, T, 0);
	glutSolidSphere(2.0, 50, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(R, 1.0, 1.0, 0.0);
	glutSolidCube(3.0);
	glPopMatrix();
	glFlush();
}

void DoDisplay_Move() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(Px, 0, 0, 0, 0, -1, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, T, 0);
	glRotatef(R, 1.0, 1.0, 0.0);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light0_position[] = { 0.0,5.0,5.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat spot_direction[] = { 0.0, 5.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
	glPopMatrix();

	glutSolidSphere(2.0, 50, 30);

	glutSolidCube(3.0);
	glFlush();
}

void DoDisplay_FollowMove() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	GLfloat light0_position[] = { 0.0,5.0,5.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat spot_direction[] = { 0.0, 5.0, 5.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

	gluLookAt(Px, 0, 0, 0, 0, -1, 0, 1, 0);

	
	glTranslatef(0, T, 0);
	glRotatef(R, 1.0, 1.0, 0.0);

	glutSolidSphere(2.0, 50, 30);

	glutSolidCube(3.0);
	glFlush();
}

int main() {
	glutCreateWindow("OpenGL");
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	MyLightInit();
	MyMaterialInit();
	glutDisplayFunc(DoDisplay_Fix);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(DoKeyboard);
	glutMainLoop();
	return 0;
}