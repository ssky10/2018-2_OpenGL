#include<windows.h>
#include<stdio.h>
#include"opengl/glut.h"
#include<stdlib.h>
#include<time.h>
#include<string>
#include<cmath>

#define WAIT	0
#define RUN		1

#define SUCCESS 0
#define FAIL 1

#define ATTACK 1
#define DEFENSE 0

void endGame();

typedef struct {
	double x,y; //���� ���� ��ġ
	double ang; //�κ� ȸ�� ����
	double L_arm_ang; //���� �� ȸ�� ����
	double R_arm_ang; //���� �� ȸ�� ����
} motion;

motion motions[5];
int user = -1;
int computer = -1;

static double _time = 0;  // Run_time ����

GLfloat R_Arm_x = 0; // ������ ���
GLfloat R_Arm_y = 0; // ������ ��
GLfloat L_Arm_x = 0; // ���� ���
GLfloat L_Arm_y = 0; // ���� ��
GLfloat R_Leg_x = 0; // ���� �����
GLfloat R_Leg_y = 0; // ���� ���Ƹ�
GLfloat L_Leg_x = 0; // �� �����
GLfloat L_Leg_y = 0; // �� ���Ƹ�
GLfloat R = 0; // ���� ���� ��ġ ������ ����
GLfloat R2 = 0;// ������ ���� ��ġ ������ ����

GLUquadricObj* cyl;// �Ǹ��� ��ü ����

static int key = 0;  // ���� ���� ���� ���� ����

char mode = DEFENSE;

char stage_user[5] = { '-','-','-','-','-' };
char stage_computer[5] = { '-','-','-','-','-' };

int try_num = 0;

int score = 0;
char str[100];

double testd[3] = { 0.0 };

/*c++ string��ü wstring��ü�� ��ȯ�ϴ� �Լ�(���򸻿��� �ʿ�)*/
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

/*�κ��� ������ ��ġ �ʱ�ȭ*/
void makeMotions() {
	motions[0] = { 0.7,0.5,-45,-180,0 }; //�������
	motions[1] = { 0.0,0.5,0,-180,-180 }; //���
	motions[2] = { -0.7,0.5,45,0,-180 }; //�������
	motions[3] = { 0.7,-0.2,-90,-180,-180 }; //����
	motions[4] = { -0.7,-0.2,90,-180,-180 }; //����
}

/*�����ʱ�ȭ �Լ�*/
void glInit(void) {
	glEnable(GL_DEPTH_TEST); // ���� ���
	glEnable(GL_NORMALIZE);  // ����ȭ
	glEnable(GL_SMOOTH);     // ���󺸰� ���
	glEnable(GL_LIGHTING);   // ���� ������

	/* ���� �޴� ������ ���� �κ� ������ ��ȭ�� ���� ���� */
	GLfloat ambientLight[] = { 0.3f,0.3f,0.3f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specref[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 400.0,300.0,-700.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(1.0, 1.0, 1.0, 1.0); // ��� ���
}

/*���ڿ��� ȭ�鿡 ���*/
void output(GLfloat x, GLfloat y, float r, float g, float b, void* font, char *string)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

/*���� �������� ȭ�鿡 ���*/
void DrawScore() {
	glPushMatrix();
	sprintf_s(str, "   user  : %c %c %c %c %c",
		stage_user[0], stage_user[1], stage_user[2], stage_user[3], stage_user[4]);
	output(-1.9, 1.7, 0.0, 0.0, 0.0, GLUT_BITMAP_9_BY_15, str);
	sprintf_s(str, "computer : %c %c %c %c %c",
		stage_computer[0], stage_computer[1], stage_computer[2], stage_computer[3], stage_computer[4]);
	output(-1.9, 1.6, 0.0, 0.0, 0.0, GLUT_BITMAP_9_BY_15, str);
	glPopMatrix();
}

void MyReshape(int w, int h) {
	GLdouble width, height;

	//��������
	if (w > h) {
		height = 2.0;
		width = 2.0 * w / h;
	}
	else {
		width = 2.0;
		height = 2.0 * w / h;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, -height, height, 2.0, -2.0); // ���� ���� ����

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
}

void Draw_Color(int i) { // ������ �׸��� �Լ�
	if (i == DEFENSE) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else {
		glColor3f(1.0, 1.0, 0.0);
	}
}

///////////�κ����� �Լ� ���ۺ�(å 304p project2 �����ڵ� ����)////////////

/*
�κ� ������ �׸��� �Լ�
*/
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);       // �� ����
	cyl = gluNewQuadric();   // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25, 0.0, 0.0);    // ���� ��� ���������� �̵�
	glRotatef(15.0, 0.0, 1.0, 0.0); // ���� ����� y���� �������� 15�� ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

/*
�κ� ���� ���� �׸��� �Լ�
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);       // �� ����
	cyl = gluNewQuadric();   // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // �޼� ������
	glRotatef(y, a, b, c);        // �Ķ���� ����ŭ ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);           // �Ǹ����� �׸�
	glPopMatrix();
}
/*
�κ� ���� �ָ�
*/
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(mode);     // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0, 0, R); // ���� �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}
/*
�κ� �������� �׸��� �Լ�
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);     // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c);  // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x���� �������� 90�� ȸ��(�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25, 0.0, 0.0); //���� ��� ���������� �̵�
	glRotatef(-15.0, 0.0, 1.0, 0.0); //���� ��� -15�� y����� ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
}
/*
�κ� ������ ���� �׸��� �Լ�
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode); // �� ����
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22);//������ �� ������
	glRotatef(y, a, b, c);// �Ķ���Ͱ� ��ŭ ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}

/*
�κ� ������ ����Ʈ �Լ�
*/

void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glTranslatef(0, 0, R2);//�����ָ� ��ġ �Ķ���͸�ŭ �̵�
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ��ü�� �׸��� �Լ�
*/
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glRotatef(x, a, b, c);//�Ķ���Ͱ� ��ŭ ȸ��
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� ������� �׸��� �Լ�
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.1, 0.0, 0.42);//���� ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ���� ���Ƹ��� �׸��� �Լ�
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.18);//���� ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ������ ������� �׸��� �Լ�
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.1, 0.0, 0.42);//������ ����� ������
	glRotatef(x, a, b, c);//�Ķ���͸�ŭ ȸ��
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// �Ǹ��� �׸�

}
/*
�κ� ������ ���Ƹ��� �׸��� �Լ�
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����

	glTranslatef(0.0, 0.0, 0.18);//������ ���Ƹ� ������
	glRotatef(y, a, b, c);//�Ķ���͸�ŭ ȸ��

	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� ���� �׸��� �Լ�
*/
void Drawneck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);//�� ����(���)
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.0, 0.0, -0.045); // �� ������
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);// �Ǹ��� �׸�
	glPopMatrix();
}
/*
�κ� �Ӹ��� �׸��� �Լ�
�κ��� �Ӹ��� �޷��ִ� �԰�
�κ��� ���� �����Ͽ���.
*/
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0);//�Ӹ� ������
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	cyl = gluNewQuadric();
	Draw_Color(mode);//���� ����
	gluSphere(cyl, 0.20, 30, 10);//�Ӹ� �׸���
								 /*���� �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(-0.16, 0.0, -0.22);//���� �� ������
	glRotatef(35.0, 0.0, 1.0, 0.0);//35�� y�� ���� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//�Ǹ��� �׸�
	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*������ �� �׸���*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	glTranslatef(0.16, 0.0, -0.22);//������ �� ������
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35�� y�� ���� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//�Ǹ��� �׸�
	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.	
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*���� �� �׸���*/
	glTranslatef(-0.1, 0.1, 0.13);//���� �� ������
	glColor3f(0.0, 0.0, 0.0);// �� �÷� ����(���)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // ó�� ���� ��ǥ�� ���� ����.
	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����

				   /*������ �� �׸���*/
	glTranslatef(0.1, 0.1, 0.13);//������ �� ������
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// ó�� ���� ��ǥ �ٽ� ����
}
/*
�ȵ���̵� ��ü ����� �׸��� �Լ�
*/
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	Drawneck(); // ���Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawR_Arm(R_Arm_x, 1, 0, 0);//�����ȶ�
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //������ȣ��
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //�����ȶ�
	DrawL_Hand(L_Arm_y, 1, 0, 0);  //������ȣ��
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0);  //������		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //�����ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0);  //������	
}

///////////�κ����� �Լ� ��(å 304p project2 �����ڵ� ����)////////////

/*��ü ����� �׷��ִ� �Լ�*/
void DrawGround() {
	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);
	cyl = gluNewQuadric();//�Ǹ��� ��ü ����

	glTranslatef(1, 0.6, -0.4);//���� ��� ��� ������
	glRotatef(90.0, 1.0, 0.0, 0.0);//�Ǹ��� 90�� x����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	gluCylinder(cyl, 0.05, 0.05, 1, 15, 1);//���� ��� ��� �׸�

	glRotatef(-90.0, 0.0, 1.0, 0.0);//�Ǹ��� 90�� y����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	gluCylinder(cyl, 0.05, 0.05, 2, 15, 1);//��� ���� �׸�

	glTranslatef(0.0, 0.0, 2.0);//������ ��� ��� ������
	glRotatef(90.0, 0.0, 1.0, 0.0);//�Ǹ��� 90�� y����� ȸ�� (�Ǹ��� ������ ���� ������ ���Ͽ�)
	gluCylinder(cyl, 0.05, 0.05, 1, 15, 1);//������ ��� ��� �׸�

	glPopMatrix();
}

/*���� �׷��ִ� �Լ�*/
void DrawBall() {
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	if (key == WAIT) {
		glTranslatef(0, -1.8, 0);
		glutSolidSphere(0.15, 15, 8);
	}
	else {
		int m = (mode == DEFENSE) ? computer : user;
		glTranslatef(-motions[m].x * (_time / 35), (-1.8 + (motions[m].y+1.8) * (_time / 35)), -1.0); //���� �κ��� ��ġ 
		glutSolidSphere(0.15 - (0.12 * (_time / 35)), 15, 8);
	}
	
	glPopMatrix();
}

/*�ȵ���̵尡 ����ϰ� �ִ� ȭ�鿡���� �Լ�*/
void waiting() {
	glLoadIdentity();//CTM �ʱ�ȭ
	L_Arm_x = 0;	//����
	R_Arm_x = 0;	//������
	R_Arm_y = 0;	//�����ȶ� ����
	L_Arm_y = 0;	//�����ȶ� ����

	R_Leg_y = 0;	//�������Ƹ� ����
	L_Leg_y = 0;	//�������Ƹ� ����
	R_Leg_x = 0;	//�����ٸ�
	L_Leg_x = 0;	//�����ٸ�


	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����
	glLoadIdentity();//CTM �ʱ�ȭ

	DrawScore();

	gluLookAt(0, 0.01, 0.3, 0, 0, 0, 0, 1, 0);

	DrawBall();
	glRotatef(-180.0, 0, 1, 0);
	DrawGround();
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);

	glTranslatef(0.0, 0.0, 0.0);//���� �κ��� ��ġ 
	DrawAndroid();
	glutSwapBuffers();
}

/*�ȵ���̵尡 �����Ҷ��� �Լ�*/
void Run() {
	int m = (mode==ATTACK)? computer : user;
	glLoadIdentity();//CTM �ʱ�ȭ

	L_Arm_x = motions[m].L_arm_ang * (_time / 35);	//����
	R_Arm_x = motions[m].R_arm_ang * (_time / 35);	//������
	R_Arm_y = 0;	//�����ȶ� ����
	L_Arm_y = 0;	//�����ȶ� ����

	R_Leg_y = 0;	//�������Ƹ� ����
	L_Leg_y = 0;	//�������Ƹ� ����
	R_Leg_x = 0;	//�����ٸ�
	L_Leg_x = 0;	//�����ٸ�

	cyl = gluNewQuadric(); //�Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); //��� ����

	glLoadIdentity();//CTM �ʱ�ȭ

	DrawScore();

	gluLookAt(0, 0.01, 0.3, 0, 0, 0, 0, 1, 0);

	DrawBall();
	glRotatef(-180.0, 0, 1, 0);//y������ �����
	DrawGround();

	glPushMatrix();// ó�� ���� ��ǥ �ٽ� ����
	glTranslatef(motions[m].x * (_time / 35), motions[m].y * (_time / 35), 0.0); //���� �κ��� ��ġ 
	glRotatef(motions[m].ang * (_time / 35), 0, 0, 1); //y������ �����
	glScalef(0.5, 0.5, 0.5);

	DrawAndroid();
	glutSwapBuffers();
}

/*�¸����� Ȯ�� �� ��������*/
int CheckVic() {
	if (user == computer) {
		if (mode == DEFENSE) {
			stage_computer[try_num] = 'X';
			mode = ATTACK;
			score++;
		}
		else {
			stage_user[try_num] = 'X';
			try_num++;
			mode = DEFENSE;
			score--;
		}
		return SUCCESS;
	}
	else {
		if (mode == DEFENSE) {
			stage_computer[try_num] = 'O';
			mode = ATTACK;
		}
		else {
			stage_user[try_num] = 'O';
			try_num++;
			mode = DEFENSE;
		}
		return FAIL;
	}
}

/*�ȵ���̵尡 �����ϴ� �ð������� Ÿ�̸�*/
void R_T_Timer(int Value) {
	_time += 1;
	if (_time < 35) {
		glutPostRedisplay();
		glutTimerFunc(40, R_T_Timer, 1);
	}
	else if (Value < 20) {
		_time = 35;
		glutTimerFunc(40, R_T_Timer, Value+1);
	}
	else {
		key = 0;
		_time = 0;
		glutPostRedisplay();
		CheckVic();
		if (try_num == 5) {
			endGame();
		}
	}
}

/*��ǻ�Ͱ� �����ϴ� �� ����*/
void ChoiceComputer() {
	srand(time(NULL));
	computer = rand()%5;
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
	case 'q':
		user = 0;
		break;
	case 'w':
		user = 1;
		break;
	case 'e':
		user = 2;
		break;
	case 'a':
		user = 3;
		break;
	case 'd':
		user = 4;
		break;
	case 's':
		ChoiceComputer();
		key = RUN;
		glutTimerFunc(40, R_T_Timer, 1);
		break;
	case '1':
		testd[0] += 0.1;
		break;
	case '2':
		testd[1] += 0.1;
		break;
	case '3':
		testd[2] += 0.1;
		break;
	case '4':
		testd[0] -= 0.1;
		break;
	case '5':
		testd[1] -= 0.1;
		break;
	case '6':
		testd[2] -= 0.1;
		break;
	case 'h':
		std::string help;
		help = "���� : �ȵ���̵� �º�����\n";
		help.append("\n���� : ������ ���� �����ѵ� ���۹�ư�� ������ ���۵˴ϴ�.\n�� ���� 5���� ��ȸ�� �־����� �ʷϻ� �κ��� ������� �κ��̰� ����� �κ��� ��ǻ�� �Դϴ�.\n");
		help.append("���ݿ��� �Է��� ������ ���� �����̸� ���� ������ ������ �κ��� �̵��ϴ� ������ �˴ϴ�.\n");
		help.append("\n-���۹�-\nq:�����ʻ��\nw:�߾ӻ��\ne:���ʻ��\na:����\nd:������\ns:����");

		std::wstring stemp = s2ws(help);
		LPCWSTR result = stemp.c_str();
		//MessageBox(0, result, L"����", MB_OK);
		MessageBoxExW(0, result, L"����", MB_OK,0);
		break;
	}
}

void MyDisplay() {
	if (key == RUN) {	
		Run();
		glPopMatrix();
	}
	else if (key == 0) {
		waiting();
		glPopMatrix();
	}
}

void MyTimer(int Value) {
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

/*���� ����� ��� �޽��� �� �� �ʱ�ȭ*/
void endGame() {
	if (score == 0) {
		MessageBoxExW(0, L"��ǻ�Ϳ� ���̽��ϴ�.", L"���", MB_OK,0);
	}else if (score < 0) {
		MessageBoxExW(0, L"��ǻ�Ϳ��� �й��ϼ̽��ϴ�.", L"���", MB_OK,0);
	}
	else {
		MessageBoxExW(0, L"��ǻ�Ϳ��� �¸��ϼ̽��ϴ�.", L"���", MB_OK,0);
	}
	user = -1;
	computer = -1;
	key = 0;  // ���� ���� ���� ���� ����

	mode = DEFENSE;

	stage_user[0] = '-';
	stage_user[1] = '-';
	stage_user[2] = '-';
	stage_user[3] = '-';
	stage_user[4] = '-';
	stage_user[5] = '-';

	stage_computer[0] = '-';
	stage_computer[1] = '-';
	stage_computer[2] = '-';
	stage_computer[3] = '-';
	stage_computer[4] = '-';
	stage_computer[5] = '-';

	try_num = 0;
	score = 0;
}

int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//���÷��� ��� ����
	glutInitWindowSize(800, 800);//������ ũ�� ����
	glutInitWindowPosition(0, 0);//������ �ʱ� ��ġ ����
	glutCreateWindow("�ȵ���̵� �º�����");//������ ����
	glInit(); // ���� �ʱ�ȭ
	makeMotions(); //��� ��ǥ �� �ʱ�ȭ
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard); //Ű���� �ݹ�
	glutTimerFunc(40, MyTimer, 1); //Ÿ�̸� �Լ�
	glutDisplayFunc(MyDisplay); //���÷���
	glutMainLoop();
	return 0;
}