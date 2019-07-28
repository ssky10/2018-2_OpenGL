#include <Windows.h>
#include <glut.h>

#define WIDTH 4
#define HEIGHT 4

GLubyte MyTexture[WIDTH][HEIGHT][3];

void FillMyTextureCheck() {
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

void MyTextureInit() {
	FillMyTextureCheck();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB,
		GL_UNSIGNED_BYTE, MyTexture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 2.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(2.0, 2.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(2.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 2.0); glVertex3f(0.0, -1.0, 0.0);
	glTexCoord2f(2.0, 2.0); glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(2.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.6, 0.2, 0.0);
	glTexCoord2f(0.0, HEIGHT - 1.0); glVertex3f(-0.5, 0.7, 0.0);
	glTexCoord2f(WIDTH - 1.0, HEIGHT - 1.0); glVertex3f(0.2, 0.8, 0.0);
	glEnd();
	glutSwapBuffers();
}

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Manual Texture Mapping");
	MyTextureInit();
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
