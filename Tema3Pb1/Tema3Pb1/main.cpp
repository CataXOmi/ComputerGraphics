/*Hearn & Baker */
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 720, winHeight = 720;
GLuint regHex, regHex2, regHex3, regHex4, regHex5;
static GLfloat rotTheta = 0.0;
double ray1, ray2, ray3, ray4, ray5;
double coord[256][256];


class scrPt
{
public:
	GLint x, y;
};

void glPrintf(int x, int y, char* sir, int lungime) {
	glColor3f(0.0, 0.0, 0.0);
	int i = 0;
	for (i = 0; i < lungime; i++) {
		glRasterPos2i(x + i * 15, y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, sir[i]);
	}
}

static void init(void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	//cerc 1
	ray1 = 100.0;
	glClearColor(0.5, 0.5, 0.5, 1.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 250; k++)
	{
		hexTheta = TWO_PI * k / 250;
		hexVertex.x = 150 + ray1 * cos(hexTheta);
		hexVertex.y = 150 + ray1 * sin(hexTheta);
		coord[0][0] = cos(hexTheta);
		coord[0][1] = sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	char sp[100];
	sprintf_s(sp, "O (%.2f,%.2f)", (float)150, (float)150);
	glPrintf(100, 175, sp, strlen(sp));
	glEndList();
	
	//cerc 2
	ray2 = 50.0;
	regHex2 = glGenLists(1);
	glNewList(regHex2, GL_COMPILE);
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	for (k = 0; k < 180; k++)
	{
		hexTheta = TWO_PI * k / 180;
		hexVertex.x = 0 + ray2 * cos(hexTheta);
		hexVertex.y = 0 + ray2 * sin(hexTheta);
		coord[1][0] = cos(hexTheta);
		coord[1][1] = sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	sprintf_s(sp, "O (%.2f,%.2f)", (float)0, (float)0);
	glPrintf(0, 20, sp, strlen(sp));
	glEndList();
	

	//cerc 3
	ray3 = 75.0;
	regHex3 = glGenLists(1);
	glNewList(regHex3, GL_COMPILE);
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glBegin(GL_POLYGON);
	for (k = 0; k < 360; k++)
	{
		hexTheta = TWO_PI * k / 360;
		hexVertex.x = 300 + ray3 * cos(hexTheta);
		hexVertex.y = 300 + ray3 * sin(hexTheta);
		coord[2][0] = cos(hexTheta);
		coord[2][1] = sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	sprintf_s(sp, "O (%.2f,%.2f)", (float)300, (float)300);
	glPrintf(300, 325, sp, strlen(sp));
	glEndList();


	//cerc 4
	ray4 = 125.0;
	regHex4 = glGenLists(1);
	glNewList(regHex4, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	for (k = 0; k < 150; k++)
	{
		hexTheta = TWO_PI * k / 150;
		hexVertex.x = -200 + ray4 * cos(hexTheta);
		hexVertex.y = -200 + ray4 * sin(hexTheta);
		coord[3][0] = cos(hexTheta);
		coord[3][1] = sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}

	glEnd();
	sprintf_s(sp, "O (%.2f,%.2f)", (float)-200, (float)-200);
	glPrintf(-200, -175, sp, strlen(sp));
	glEndList();
	
	//cerc 5
	ray5 = 150.0;
	regHex5 = glGenLists(1);
	glNewList(regHex5, GL_COMPILE);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 250; k++)
	{
		hexTheta = TWO_PI * k / 250;
		hexVertex.x = 450 + ray5 * cos(hexTheta);
		hexVertex.y = 500 + ray5 * sin(hexTheta);
		coord[4][0] = cos(hexTheta);
		coord[4][1] = sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	sprintf_s(sp, "O (%.2f,%.2f)", (float)450, (float)500);
	glPrintf(450, 525, sp, strlen(sp));
	glEndList();


}

void displayHex(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(1.0f);
	glPointSize(1.0f);

	glCallList(regHex);

	//centrul cercului 1
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(150, 150);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	//raza cercului 1
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(150.0, 150.0);
	glVertex2d(150.0 + ray1 * coord[0][0], 150.0 + ray1 * coord[0][1]);
	glEnd();

	glLineWidth(1.0f);
	glPointSize(1.0f);

	glCallList(regHex2);
	
	//centrul cercului 2
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(0, 0);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	//raza cercului 2
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(0 + ray2 * coord[1][0], 0 + ray2 * coord[1][1]);
	glEnd();

	glLineWidth(1.0f);
	glPointSize(1.0f);

	glCallList(regHex3);
	
	//centrul cercului 3
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(300, 300);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	//raza cercului 3
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(300.0, 300.0);
	glVertex2d(300.0 + ray3 * coord[2][0], 300.0 + ray3 * coord[2][1]);
	glEnd();

	glLineWidth(1.0f);
	glPointSize(1.0f);

	glCallList(regHex4);
	
	//centrul cercului 4
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(-200, -200);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	//raza cercului 4
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(-200.0, -200.0);
	glVertex2d(-200.0 + ray4 * coord[3][0], -200.0 + ray4 * coord[3][1]);
	glEnd();

	glLineWidth(1.0f);
	glPointSize(1.0f);

	glCallList(regHex5);

	//centrul cercului 5
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(450, 500);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	//raza cercului 5
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(450.0, 500.0);
	glVertex2d(450.0 + ray5 * coord[4][0], 500.0 + ray5 * coord[4][1]);
	glEnd();

	glPopMatrix();


	glFlush();
}


void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-720.0, 720.0, -720.0, 720.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Hexagon - utilizarea listelor de display");

	init();
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();

}



