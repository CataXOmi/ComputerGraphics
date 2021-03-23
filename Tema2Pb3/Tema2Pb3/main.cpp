#include<windows.h>
#include<GL/glew.h>
#include<gl/freeglut.h>
#include<iostream>

using namespace std;

typedef struct punct
{
	float x;
	float y;
};

int nrp = 8;
punct vp[8]; // de forma:[PBlue,PMagenta,PWhite,PCyan,PBlack,PRed,PYellow,PGreen]


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(0.5, 0.5, 0.5, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 10.0, 0.0, 10.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{

	// vom desena fetele de sus si jos ale cubului si linia de la punctul blue la punctul black
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2i(vp[0].x, vp[0].y);
	glVertex2i(vp[1].x, vp[1].y);
	glVertex2i(vp[2].x, vp[2].y);
	glVertex2i(vp[3].x, vp[3].y);
	glVertex2i(vp[0].x, vp[0].y);
	glVertex2i(vp[4].x, vp[4].y);
	glVertex2i(vp[5].x, vp[5].y);
	glVertex2i(vp[6].x, vp[6].y);
	glVertex2i(vp[7].x, vp[7].y);
	glVertex2i(vp[4].x, vp[4].y);
	glEnd();

	// vom desena linia de la cyan la green
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2i(vp[3].x, vp[3].y);
	glVertex2i(vp[7].x, vp[7].y);
	glEnd();

	// vom desena linia de la white la yellow
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2i(vp[2].x, vp[2].y);
	glVertex2i(vp[6].x, vp[6].y);
	glEnd();

	// vom desena linia de la magenta la red
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2i(vp[1].x, vp[1].y);
	glVertex2i(vp[5].x, vp[5].y);
	glEnd();

	//punctele colorate
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[0].x, vp[0].y);
	glColor3f(1, 0, 1); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[1].x, vp[1].y);
	glColor3f(1, 1, 1); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[2].x, vp[2].y);
	glColor3f(0, 1, 1); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[3].x, vp[3].y);
	glColor3f(0, 0, 0); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[4].x, vp[4].y);
	glColor3f(1, 0, 0); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[5].x, vp[5].y);
	glColor3f(1, 1, 0); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[6].x, vp[6].y);
	glColor3f(0, 1, 0); // culoarea punctului de intersectie: albastru
	glVertex2i(vp[7].x, vp[7].y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	
	//PBlue
	vp[0].x = 4;
	vp[0].y = 8;
	//PMagenta
	vp[1].x = 8;
	vp[1].y = 8;
	//PWhite
	vp[2].x = 6;
	vp[2].y = 6;
	//PCyan
	vp[3].x = 2;
	vp[3].y = 6;
	//PBlack
	vp[4].x = 4;
	vp[4].y = 4;
	//PRed
	vp[5].x = 8;
	vp[5].y = 4;
	//PYellow
	vp[6].x = 6;
	vp[6].y = 2;
	//PGreen
	vp[7].x = 2;
	vp[7].y = 2;

	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(75, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(800, 800); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	
}