#include "opengl/glut.h"

int ClipPlane();
int CullFace();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	ClipPlane();
	//CullFace();
	return 0;
}
