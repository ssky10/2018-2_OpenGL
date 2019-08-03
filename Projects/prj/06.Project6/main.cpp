#include "opengl/glut.h"

int culling();
int projection();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	culling();
	//projection();
	return 0;
}