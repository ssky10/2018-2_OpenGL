#include <stdio.h>
#include "opengl/glut.h"

void MyLightInit() {
	GLfloat light0_ambient[] = { 1.0,0.0,0.0,1.0 };  //la:�ֺ��� Ư��1
	GLfloat light0_diffuse[] = { 1.0,0.0,0.0,1.0 };  //ld:Ȯ�걤 Ư��1
	GLfloat light0_specular[] = { 1.0,1.0,1.0,1.0 }; //ls:��鱤 Ư��1
	GLfloat light1_ambient[] = { 1.0,1.0,1.0,1.0 };  //la:�ֺ��� Ư��2
	GLfloat light1_diffuse[] = { 0.0,1.0,0.0,1.0 };  //ld:Ȯ�걤 Ư��2
	GLfloat light1_specular[] = { 0.0,1.0,1.0,1.0 }; //ls:��鱤 Ư��2
	//GLfloat light0_ambient[] = { 1.0,0.0,0.0,1.0 };  //la:�ֺ��� Ư��3
	//GLfloat light0_diffuse[] = { 0.0,1.0,0.0,1.0 };  //ld:Ȯ�걤 Ư��3
	//GLfloat light0_specular[] = { 1.0,1.0,1.0,1.0 }; //ls:��鱤 Ư��3
	//GLfloat light0_ambient[] = { 1.0,0.0,0.0,1.0 };  //la:�ֺ��� Ư��4
	//GLfloat light0_diffuse[] = { 1.0,0.0,0.0,1.0 };  //ld:Ȯ�걤 Ư��4
	//GLfloat light0_specular[] = { 0.0,1.0,1.0,1.0 }; //ls:��鱤 Ư��4

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.0);
}

void MyMaterialInit() {
	GLfloat material_ambient[] = { 0.1,0.1,0.1,1.0 }; //Ka:�ֺ��� ���
	GLfloat material_diffuse[] = { 0.8,0.8,0.8,1.0 }; //Kd:Ȯ�걤 ���
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 }; //Ks:��鱤 ���
	GLfloat material_shiniess[] = { 5.0 }; //n:���� ���

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
	glMatrixMode(GL_POSITION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void DoDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat light0_position[] = { -0.3,-0.3,1.0,1.0 };
	GLfloat light1_position[] = { 0.3,-0.3,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();
	glFlush();
}

int main() {
	glutCreateWindow("OpenGL");
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	MyLightInit();
	MyMaterialInit();
	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}