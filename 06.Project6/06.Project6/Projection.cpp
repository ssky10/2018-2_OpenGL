#include <Windows.h>
#include <glut.h>

int gWidth, gHeight;

void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*회색사각형 평면위에 주전자 생성*/
void DrawScene() {
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glEnd();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.7);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.5);
	glutWireTeapot(1.0);
	glPopMatrix();
}

void MyDisplay() { 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	//좌상단
	glViewport(0, 0, gWidth / 2, gHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	//우상단
	glViewport(gWidth / 2, 0, gWidth / 2, gHeight / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();

	//좌하단
	glViewport(0, gHeight/2, gWidth / 2, gHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	DrawScene();
	glPopMatrix();

	//우하단
	glViewport(gWidth/2, gHeight/2, gWidth / 2, gHeight / 2);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(30, (GLdouble)gWidth/gHeight, 3.0, 50.0);
	glPushMatrix();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DrawScene();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();
}

void MyReshape(int w, int h) {
	GLdouble width, height;
	gWidth = w;
	gHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//비율조정
	if (gWidth > gHeight) {
		height = 2.0;
		width = 2.0 * gWidth / gHeight;
	}
	else {
		width = 2.0;
		height = 2.0 * gHeight / gWidth;
	}

	glOrtho(-width, width, -height, height, 0.5, 10.0); //가시부피크기 설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main() {
	gWidth = 500;
	gHeight = 500;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(gWidth, gHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Projection with multiple viewports");
	Init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}