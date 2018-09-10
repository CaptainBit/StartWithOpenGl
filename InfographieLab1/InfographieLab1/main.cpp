/* Starter project */

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
#include "ShaderLoader.h"

//Define
	//KEY
	#define KEY_UP  101
	#define KEY_DOWN 103
	#define KEY_RIGHT 102
	#define KEY_LEFT  100
	#define KEY_F1 1
	#define KEY_F2 2
	#define KEY_F3 3
	//WINDOW SIZE
	#define WINDOW_WIDTH 800
	#define WINDOW_HEIGHT 600
	
//header
void initGlut(int * argc, char * argv[]);
void createWindow(int * win);
void refreshGraphics();
void touchesClavier(unsigned char touche, int x, int y);
void touchesSpecialesClavier(int touche, int x, int y);
void randomColor(float &r, float &v, float &b);
//Fonction principale d'ex�cution
int main(int argc, char **argv)
{
	int win;
	initGlut(&argc, argv);
	createWindow(&win);
	glewInit();
	ShaderLoader shaderLoader;
	GLuint program = shaderLoader.CreateProgram((char*)"MyFirstShader.glsl", (char*)"FragmentShader.glsl");
	glUseProgram(program);
	glutMainLoop();
	
	return 0;

}

//Fonction qui init glut
void initGlut(int * argc, char * argv[]) { 
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	
}

//Fonction qui cr�er la fen�tre
void createWindow(int * win) {
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	*win = glutCreateWindow("Laboratoire 1");
	glClearColor(1.0, 0.0, 0.0, 0);
	glutDisplayFunc(refreshGraphics);
	glutKeyboardFunc(touchesClavier);
	glutSpecialFunc(touchesSpecialesClavier);
}

//Rafraichissement de la page 
void refreshGraphics(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
}

//Entr�es au clavier
void touchesClavier(unsigned char touche, int x, int y) {

	switch (touche)
	{
		case 'r':
			glClearColor(1, 0, 0, 0);
			break;
		case 'b':
			glClearColor(0, 0, 1, 0);
			break;
		case 'v':
			glClearColor(0, 1, 0, 0);
			break;
		case 'n':
			glClearColor(0, 0, 0, 0);
			break;
		case 'm':
			glClearColor(1, 0, 1, 0);
			break;
		case 't':
			glClearColor(0, 1, 1, 0);
			break;
		case 'o':
			glClearColor(1, 0.5, 0.2, 0);
			break;
		case 27:
			glutLeaveMainLoop();
			break;
		case 'z':
			float r, v, b;
			randomColor(r, v, b);
			glClearColor(r, v, b, 0);
			break;
		default:
			glClearColor(1, 1, 1, 0);
	}
	glutPostRedisplay();

}

void touchesSpecialesClavier(int touche, int x, int y) {

	//Get Size window
	float width = glutGet(GLUT_WINDOW_WIDTH);
	float height = glutGet(GLUT_WINDOW_HEIGHT);
	switch (touche)
	{
		case KEY_UP:
			glutPositionWindow(-1,-1);
			glutReshapeWindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			break;

		case KEY_DOWN:
			glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;

		case KEY_RIGHT:
			glutReshapeWindow(width+50, height+50);
			break;

		case KEY_LEFT:
			glutReshapeWindow(width - 50, height - 50);
			break;

		case KEY_F1:
			glutPositionWindow(-1, -1);
			break;

		case KEY_F2:
			glutPositionWindow(GetSystemMetrics(SM_CXSCREEN)-width+1, GetSystemMetrics(SM_CYSCREEN)-height+1);
			break;
		
		case KEY_F3:
			glutPositionWindow(GetSystemMetrics(SM_CXSCREEN) / 2 - (width / 2), GetSystemMetrics(SM_CYSCREEN) / 2 - (height / 2));

		default:
			break;
	}
}
void randomColor(float &r, float &v, float &b) {
	r = rand()%255;
	r = r / 255;
	v = rand() % 255;
	v = v / 255;
	b = rand() % 255;
	b = b / 255;
}

