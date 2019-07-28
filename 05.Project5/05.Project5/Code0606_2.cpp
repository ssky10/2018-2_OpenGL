#include <windows.h>
#include <glut.h>

static int Day = 0, Time = 0;
static int vDay = 0, vTime = 0;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16); //Sun
	glPushMatrix();
		glRotatef((GLfloat)vDay, 0.0, 1.0, 0.0);
		glTranslatef(0.35, 0.0, 0.0);
		glRotatef((GLfloat)vTime, 0.0, 1.0, 0.0);
		glColor3f(0.3, 0.6, 0.4);
		glutWireSphere(0.07, 10, 8); //Venus
	glPopMatrix();
	glPushMatrix();
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
		glTranslatef(0.7, 0.0, 0.0);
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);
		glutWireSphere(0.1, 10, 8); //Earth
		glPushMatrix();
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0.0);
			glColor3f(0.9, 0.8, 0.2);
			glutWireSphere(0.04, 10, 8); //Moon
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void MyTimer(int value) {
	Day = (Day + 10) % 360;
	Time = (Time + 5) % 360;
	vDay = (vDay + 16) % 360;
	vTime = (vTime + 10) % 360;
	glutPostRedisplay();
	glutTimerFunc(150, MyTimer, 1);
}

int main() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System Orbit");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(150, MyTimer, 1);
	glutMainLoop();
	return 0;
}