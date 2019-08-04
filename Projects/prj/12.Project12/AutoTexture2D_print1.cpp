#include <Windows.h>
#include "opengl/glut.h"

#define WIDTH 3
#define HEIGHT 3

GLubyte MyTexture[WIDTH][HEIGHT][3];

GLfloat mat_diffuse[] = { 0.25,0.25,1.0,0.0 };
GLfloat mat_specular[] = { 1.0,1.0,1.0,0.0 };
GLfloat light_position[] = { 10.0,10.0,20.0,1.0 };

GLfloat MyPlane000[] = { 0.0,0.0,0.0,0.0 };
GLfloat MyPlane111[] = { 1.5,1.5,1.5,0.0 };
GLfloat MyPlane100[] = { 1.5,0.0,0.0,0.0 };
GLfloat MyPlane110[] = { 1.5,1.5,0.0,0.0 };
GLfloat MyPlane101[] = { 1.5,0.0,1.5,0.0 };
GLfloat Rx = 0.0, Ry = 0.0, Rz = 0.0;

void FillMyTextureCheck2() {
	int s, t;
	for (s = 0; s < WIDTH; s++) {
		for (t = 0; t < HEIGHT; t++) {
			GLubyte intensity = ((s + t) % 2) * 255;
			MyTexture[s][t][0] = intensity;
			MyTexture[s][t][1] = intensity;
			MyTexture[s][t][2] = intensity;
		}
	}
}

void MyInit() {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	FillMyTextureCheck2();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB,
		GL_UNSIGNED_BYTE, MyTexture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, MyPlane111);
	glEnable(GL_TEXTURE_GEN_S);

	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGenfv(GL_T, GL_OBJECT_PLANE, MyPlane111);
	//glEnable(GL_TEXTURE_GEN_T);
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40., (GLfloat)w / (GLfloat)h, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -1.0);
}

void MyDisplay2() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotated(Rx, 1.0, 0.0, 0.0);
	glRotated(Ry, 0.0, 1.0, 0.0);
	glRotated(Rz, 0.0, 0.0, 1.0);
	//glutSolidSphere(1.5, 50, 50);
	glutSolidTeapot(1.5);
	glPopMatrix();
	glutSwapBuffers();
}

void DoKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1': Rx += 1; break;
	case '2': Ry += 1; break;
	case '3': Rz += 1; break;
	case '4': Rx = Ry = Rz = 0; break;
	}
	glutPostRedisplay();
}

int AutoTexture2D() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Auto Texture Mapping");
	glutKeyboardFunc(DoKeyboard);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay2);
	MyInit();
	glutMainLoop();
	return 0;
}