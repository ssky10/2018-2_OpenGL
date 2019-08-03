#include "opengl/glut.h"

int ManualTexture();
int AutoTexture2D();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	ManualTexture();
	//AutoTexture2D();
	return 0;
}
