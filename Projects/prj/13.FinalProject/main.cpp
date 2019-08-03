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
	double x,y; //최종 도착 위치
	double ang; //로봇 회전 각도
	double L_arm_ang; //왼쪽 팔 회전 각도
	double R_arm_ang; //왼쪽 팔 회전 각도
} motion;

motion motions[5];
int user = -1;
int computer = -1;

static double _time = 0;  // Run_time 변수

GLfloat R_Arm_x = 0; // 오른쪽 어깨
GLfloat R_Arm_y = 0; // 오른쪽 팔
GLfloat L_Arm_x = 0; // 왼쪽 어깨
GLfloat L_Arm_y = 0; // 왼쪽 팔
GLfloat R_Leg_x = 0; // 오른 허벅지
GLfloat R_Leg_y = 0; // 오른 종아리
GLfloat L_Leg_x = 0; // 왼 허벅지
GLfloat L_Leg_y = 0; // 왼 종아리
GLfloat R = 0; // 왼쪽 로켓 펀치 움직임 변수
GLfloat R2 = 0;// 오른쪽 로켓 펀치 움직임 변수

GLUquadricObj* cyl;// 실린더 객체 선언

static int key = 0;  // 동작 모드와 색상 변경 변수

char mode = DEFENSE;

char stage_user[5] = { '-','-','-','-','-' };
char stage_computer[5] = { '-','-','-','-','-' };

int try_num = 0;

int score = 0;
char str[100];

double testd[3] = { 0.0 };

/*c++ string객체 wstring객체로 변환하는 함수(도움말에서 필요)*/
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

/*로봇의 움직임 위치 초기화*/
void makeMotions() {
	motions[0] = { 0.7,0.5,-45,-180,0 }; //좌측상단
	motions[1] = { 0.0,0.5,0,-180,-180 }; //상단
	motions[2] = { -0.7,0.5,45,0,-180 }; //우측상단
	motions[3] = { 0.7,-0.2,-90,-180,-180 }; //좌측
	motions[4] = { -0.7,-0.2,90,-180,-180 }; //우측
}

/*지엘초기화 함수*/
void glInit(void) {
	glEnable(GL_DEPTH_TEST); // 깊이 사용
	glEnable(GL_NORMALIZE);  // 정규화
	glEnable(GL_SMOOTH);     // 색상보간 사용
	glEnable(GL_LIGHTING);   // 지엘 조명사용

	/* 빛을 받는 각도에 따라 로봇 색깔의 변화를 위한 설정 */
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

	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경 흰색
}

/*문자열을 화면에 띄움*/
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

/*현재 점수판을 화면에 띄움*/
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

	//비율조정
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
	glOrtho(-width, width, -height, height, 2.0, -2.0); // 가시 범위 설정

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
}

void Draw_Color(int i) { // 색상을 그리는 함수
	if (i == DEFENSE) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else {
		glColor3f(1.0, 1.0, 0.0);
	}
}

///////////로봇관련 함수 시작부(책 304p project2 예제코드 참조)////////////

/*
로봇 왼팔을 그리는 함수
*/
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);       // 색 설정
	cyl = gluNewQuadric();   // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0);    // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축을 기준으로 15도 회전
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

/*
로봇 왼쪽 손을 그리는 함수
*/
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);       // 색 설정
	cyl = gluNewQuadric();   // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c);        // 파라미터 값만큼 회전
	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);           // 실린더를 그림
	glPopMatrix();
}
/*
로봇 왼쪽 주먹
*/
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(mode);     // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R); // 왼쪽 주먹 위치를 파라미터만큼 이동
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}
/*
로봇 오른팔을 그리는 함수
*/
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);     // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c);  // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축을 기준으로 90도 회전(실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); //우측 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); //우측 어깨 -15도 y축기준 회전
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
}
/*
로봇 오른쪽 손을 그리는 함수
*/
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode); // 색 설정
	cyl = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22);//오른쪽 손 시작점
	glRotatef(y, a, b, c);// 파라미터값 만큼 회전
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}

/*
로봇 오른쪽 로켓트 함수
*/

void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric(); //실린더 객체 생성
	glTranslatef(0, 0, R2);//오른주먹 위치 파라미터만큼 이동
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 몸체를 그리는 함수
*/
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glRotatef(x, a, b, c);//파라미터값 만큼 회전
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 왼쪽 허벅지를 그리는 함수
*/
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.1, 0.0, 0.42);//왼쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 왼쪽 종아리를 그리는 함수
*/
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.18);//왼쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 오른쪽 허벅지를 그리는 함수
*/
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.1, 0.0, 0.42);//오른쪽 허벅지 시작점
	glRotatef(x, a, b, c);//파라미터만큼 회전
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);// 실린더 그림

}
/*
로봇 오른쪽 종아리를 그리는 함수
*/
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(mode);
	cyl = gluNewQuadric();//실린더 객체 생성

	glTranslatef(0.0, 0.0, 0.18);//오른쪽 종아리 시작점
	glRotatef(y, a, b, c);//파라미터만큼 회전

	gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 목을 그리는 함수
*/
void Drawneck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);//색 지정(흰색)
	cyl = gluNewQuadric();//실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.0, 0.0, -0.045); // 목 시작점
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1);// 실린더 그림
	glPopMatrix();
}
/*
로봇 머리를 그리는 함수
로봇의 머리에 달려있는 뿔과
로봇의 눈을 설정하였다.
*/
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0);//머리 시작점
	glPushMatrix();// 처음 저장 좌표 다시 저장
	cyl = gluNewQuadric();
	Draw_Color(mode);//색깔 설정
	gluSphere(cyl, 0.20, 30, 10);//머리 그리기
								 /*왼쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(-0.16, 0.0, -0.22);//왼쪽 뿔 시작점
	glRotatef(35.0, 0.0, 1.0, 0.0);//35도 y축 기준 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*오른쪽 뿔 그리기*/
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	glTranslatef(0.16, 0.0, -0.22);//오른쪽 뿔 시작점
	glRotatef(-35.0, 0.0, 1.0, 0.0);//-35도 y축 기준 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);//실린더 그림
	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.	
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*왼쪽 눈 그리기*/
	glTranslatef(-0.1, 0.1, 0.13);//왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0);// 눈 컬러 설정(흑색)
	gluSphere(cyl, 0.03, 10, 10);

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

				   /*오른쪽 눈 그리기*/
	glTranslatef(0.1, 0.1, 0.13);//오른쪽 눈 시작점
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();// 처음 저장 좌표 다시 저장
}
/*
안드로이드 전체 모습을 그리는 함수
*/
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	Drawneck(); // 목함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x, 1, 0, 0);//우측팔뚝
	DrawR_Hand(R_Arm_y, 1, 0, 0);  //우측팔호출
	DrawL_Arm(L_Arm_x, 1, 0, 0);   //좌측팔뚝
	DrawL_Hand(L_Arm_y, 1, 0, 0);  //좌측손호출
	DrawL_Legs(L_Leg_x, 1, 0, 0);  //좌측다리
	DrawL_foot(L_Leg_y, 1, 0, 0);  //좌측발		 
	DrawR_Legs(R_Leg_x, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측발	
}

///////////로봇관련 함수 끝(책 304p project2 예제코드 참조)////////////

/*전체 배경을 그려주는 함수*/
void DrawGround() {
	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);
	cyl = gluNewQuadric();//실린더 객체 생성

	glTranslatef(1, 0.6, -0.4);//왼쪽 골대 기둥 시작점
	glRotatef(90.0, 1.0, 0.0, 0.0);//실린더 90도 x축기준 회전 (실린더 생성시 각도 변경을 위하여)
	gluCylinder(cyl, 0.05, 0.05, 1, 15, 1);//왼쪽 골대 기둥 그림

	glRotatef(-90.0, 0.0, 1.0, 0.0);//실린더 90도 y축기준 회전 (실린더 생성시 각도 변경을 위하여)
	gluCylinder(cyl, 0.05, 0.05, 2, 15, 1);//골대 위쪽 그림

	glTranslatef(0.0, 0.0, 2.0);//오른쪽 골대 기둥 시작점
	glRotatef(90.0, 0.0, 1.0, 0.0);//실린더 90도 y축기준 회전 (실린더 생성시 각도 변경을 위하여)
	gluCylinder(cyl, 0.05, 0.05, 1, 15, 1);//오른쪽 골대 기둥 그림

	glPopMatrix();
}

/*공을 그려주는 함수*/
void DrawBall() {
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	if (key == WAIT) {
		glTranslatef(0, -1.8, 0);
		glutSolidSphere(0.15, 15, 8);
	}
	else {
		int m = (mode == DEFENSE) ? computer : user;
		glTranslatef(-motions[m].x * (_time / 35), (-1.8 + (motions[m].y+1.8) * (_time / 35)), -1.0); //최초 로봇의 위치 
		glutSolidSphere(0.15 - (0.12 * (_time / 35)), 15, 8);
	}
	
	glPopMatrix();
}

/*안드로이드가 대기하고 있는 화면에서의 함수*/
void waiting() {
	glLoadIdentity();//CTM 초기화
	L_Arm_x = 0;	//왼팔
	R_Arm_x = 0;	//오른팔
	R_Arm_y = 0;	//우측팔뚝 각도
	L_Arm_y = 0;	//좌측팔뚝 각도

	R_Leg_y = 0;	//우측종아리 각도
	L_Leg_y = 0;	//좌측종아리 각도
	R_Leg_x = 0;	//우측다리
	L_Leg_x = 0;	//좌측다리


	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정
	glLoadIdentity();//CTM 초기화

	DrawScore();

	gluLookAt(0, 0.01, 0.3, 0, 0, 0, 0, 1, 0);

	DrawBall();
	glRotatef(-180.0, 0, 1, 0);
	DrawGround();
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);

	glTranslatef(0.0, 0.0, 0.0);//최초 로봇의 위치 
	DrawAndroid();
	glutSwapBuffers();
}

/*안드로이드가 동작할때의 함수*/
void Run() {
	int m = (mode==ATTACK)? computer : user;
	glLoadIdentity();//CTM 초기화

	L_Arm_x = motions[m].L_arm_ang * (_time / 35);	//왼팔
	R_Arm_x = motions[m].R_arm_ang * (_time / 35);	//오른팔
	R_Arm_y = 0;	//우측팔뚝 각도
	L_Arm_y = 0;	//좌측팔뚝 각도

	R_Leg_y = 0;	//우측종아리 각도
	L_Leg_y = 0;	//좌측종아리 각도
	R_Leg_x = 0;	//우측다리
	L_Leg_x = 0;	//좌측다리

	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	glLoadIdentity();//CTM 초기화

	DrawScore();

	gluLookAt(0, 0.01, 0.3, 0, 0, 0, 0, 1, 0);

	DrawBall();
	glRotatef(-180.0, 0, 1, 0);//y축으로 기울임
	DrawGround();

	glPushMatrix();// 처음 저장 좌표 다시 저장
	glTranslatef(motions[m].x * (_time / 35), motions[m].y * (_time / 35), 0.0); //최초 로봇의 위치 
	glRotatef(motions[m].ang * (_time / 35), 0, 0, 1); //y축으로 기울임
	glScalef(0.5, 0.5, 0.5);

	DrawAndroid();
	glutSwapBuffers();
}

/*승리여부 확인 및 점수저장*/
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

/*안드로이드가 동작하는 시간에서의 타이머*/
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

/*컴퓨터가 선택하는 값 저장*/
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
		help = "게임 : 안드로이드 승부차기\n";
		help.append("\n설명 : 방향을 먼저 선택한뒤 시작버튼을 누르면 시작됩니다.\n총 각각 5번의 기회가 주어지고 초록색 로봇이 사용자의 로봇이고 노란색 로봇은 컴퓨터 입니다.\n");
		help.append("공격에서 입력한 방향은 공의 방향이며 방어에서 선택한 방향은 로봇이 이동하는 방향이 됩니다.\n");
		help.append("\n-조작법-\nq:오른쪽상단\nw:중앙상단\ne:왼쪽상단\na:왼쪽\nd:오른쪽\ns:시작");

		std::wstring stemp = s2ws(help);
		LPCWSTR result = stemp.c_str();
		//MessageBox(0, result, L"도움말", MB_OK);
		MessageBoxExW(0, result, L"도움말", MB_OK,0);
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

/*게임 종료시 결과 메시지 및 값 초기화*/
void endGame() {
	if (score == 0) {
		MessageBoxExW(0, L"컴퓨터와 비기셨습니다.", L"결과", MB_OK,0);
	}else if (score < 0) {
		MessageBoxExW(0, L"컴퓨터에게 패배하셨습니다.", L"결과", MB_OK,0);
	}
	else {
		MessageBoxExW(0, L"컴퓨터에게 승리하셨습니다.", L"결과", MB_OK,0);
	}
	user = -1;
	computer = -1;
	key = 0;  // 동작 모드와 색상 변경 변수

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//디스플레이 모드 설정
	glutInitWindowSize(800, 800);//윈도우 크기 설정
	glutInitWindowPosition(0, 0);//윈도우 초기 위치 설정
	glutCreateWindow("안드로이드 승부차기");//윈도우 생성
	glInit(); // 조명 초기화
	makeMotions(); //모션 좌표 값 초기화
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard); //키보드 콜백
	glutTimerFunc(40, MyTimer, 1); //타이머 함수
	glutDisplayFunc(MyDisplay); //디스플레이
	glutMainLoop();
	return 0;
}