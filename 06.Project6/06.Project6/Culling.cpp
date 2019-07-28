#include <Windows.h>
#include <glut.h>
#include <stdio.h>

GLboolean bCullFace = GL_FALSE; //후면제거모드 플래그
GLboolean bCcwFront = GL_TRUE; //전면방향 플래그

void DoMenu(int value) {
	switch (value)
	{
	case 1: bCullFace = GL_TRUE; break;
	case 2: bCullFace = GL_FALSE; break;
	case 3: bCcwFront = GL_TRUE; break;
	case 4: bCcwFront = GL_FALSE; break;
	}
	char info[128];
	sprintf_s(info, "Cull = %s, Front = %s", bCullFace ? "ON" : "OFF", bCcwFront ? "CCW" : "CW");
	glutSetWindowTitle(info);
	glutPostRedisplay();
}

void DoDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (bCullFace)
		glEnable(GL_CULL_FACE); //후면제거모드 활성화
	else
		glDisable(GL_CULL_FACE); //후면제거모드 비활성화
	glFrontFace(bCcwFront ? GL_CCW : GL_CW); //전면방향 설정(CCW:반시계방향/CW:시계방향)

	//반시계방향 삼각형(법선벡터:모니터 앞방향)
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.5); //상단점
	glVertex2f(-0.9, -0.5); //좌하단점
	glVertex2f(-0.1, -0.5); //우하단점
	glEnd();

	//시계방향 삼각형(법선벡터:모니터 뒷방향)
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.5, 0.5); //상단점
	glVertex2f(0.9, -0.5); //우하단점
	glVertex2f(0.1, -0.5); //좌하단점
	glEnd();

	glFlush();
}

int main() {
	glutInitWindowSize(500, 300);
	glutCreateWindow("후면제거 연습");
	glutDisplayFunc(DoDisplay);
	glutCreateMenu(DoMenu);
	glutAddMenuEntry("CullFace ON", 1);
	glutAddMenuEntry("CullFace OFF", 2);
	glutAddMenuEntry("CCW", 3);
	glutAddMenuEntry("CW", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}