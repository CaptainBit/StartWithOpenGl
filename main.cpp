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
void createDrawing();
void mouseClicks(int button, int state, int x, int y);

//Fonction principale d'exécution
int main(int argc, char **argv)
{
	int win;
	initGlut(&argc, argv);
	createWindow(&win);
	glewInit();
	ShaderLoader shaderLoader;
	GLuint program = shaderLoader.CreateProgram((char*)"MyFirstShader.glsl", (char*)"FragmentShader.glsl");
	glUseProgram(program);
	createDrawing();
	glutMainLoop();
	return 0;

}

//Fonction qui init glut
void initGlut(int * argc, char * argv[]) { 
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	
}

//Fonction qui créer la fenêtre
void createWindow(int * win) {
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	*win = glutCreateWindow("Laboratoire 1");
	glClearColor(0.0, 0.0, 0.0, 0);
	glutDisplayFunc(refreshGraphics);
	glutKeyboardFunc(touchesClavier);
	glutSpecialFunc(touchesSpecialesClavier);
	
}

//Rafraichissement de la page 
void refreshGraphics(void) {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glDrawArrays(GL_LINE_LOOP,0,5);
	
	glFlush();
}

//Entrées au clavier
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

void createDrawing()
{
	//For the vertices
	GLfloat sommets[20] = { -0.5f, 0.0f, 0.0f,1.0f,   0.5f, 0.0f, 0.0f,1.0f,   -0.25f, -1.0f, 0.0f,1.0f,   0.0f, 0.5f, 0.0f, 1.0f,   0.25f, -1.0f, 0.0f,1.0f };
	GLuint bufferV;
	glGenBuffers(1, &bufferV);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,bufferV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sommets), &sommets, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//For the color
	GLfloat colors[20] = { 0.5f, 0.0f, 0.0f,1.0f,   0.5f, 0.0f, 0.0f,1.0f,   0.0f, 1.0f, 0.0f,1.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.3f,1.0f };
	GLuint bufferC;
	glGenBuffers(1, &bufferC);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, bufferC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
void mouseClicks(int button, int state, int x, int y) 
{

}