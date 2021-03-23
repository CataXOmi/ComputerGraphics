#include <windows.h>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include <math.h>

using namespace std;

typedef struct punct
{
	float x;
	float y;
	float z;
};

punct A, B, C, M, D, n, vect[256], prods[256], O1, O2;

void vectori(punct A, punct B, int poz)
{
	vect[poz].x = B.x - A.x;
	vect[poz].y = B.y - A.y;
	vect[poz].z = B.z - A.z;
}

void prodvect(punct v1, punct v2, int poz)
{

	float coordi, coordj, coordk;
	coordi = v1.y * v2.z - v1.z * v2.y;
	coordj = v1.x * v2.z - v1.z * v2.x;
	coordk = v1.x * v2.y - v1.y * v2.x;

	if (coordi == 0)
		coordi = abs(coordi);

	if (coordj == 0)
		coordj = abs(coordj);

	if (coordk == 0)
		coordk = abs(coordk);

	prods[poz].x = coordi;
	prods[poz].y = coordj;
	prods[poz].z = coordk;
}


GLint winWidth = 600, winHeight = 600;
punct PO0, Pref, V;

GLfloat xwMin = -15.0, ywMin = -5.0, xwMax = 15.0, ywMax = 5.0;

GLfloat dnear = -15.0, dfar = 15.0;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PO0.x, PO0.y, PO0.z, Pref.x, Pref.y, Pref.z, V.x, V.y, V.z);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

// POLIGONUL ABDC
void desen2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(6.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(A.x, A.y, A.z);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(B.x, B.y, B.z);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(D.x, D.y, D.z);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(C.x, C.y, C.z);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(M.x, M.y, M.z);
	glEnd();

	//glutPostRedisplay(); comanda glutului sa reapeleze aceasta functie

	glFlush();
}

void mouse2(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			PO0 = O1;
		init();
		desen2();
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			PO0 = O2;
		init();
		desen2();
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			{
			 glFrontFace(GL_CW);
			 //glEnable(GL_CULL_FACE);
			 //glCullFace(GL_FRONT);/GL_FRONT_AND_BACK
			 glShadeModel(GL_FLAT);//GL_SMOOTH
			}
		init();
		desen2();
		break;
	}
}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main(int argc, char** argv)
{
	//puncte A=(6,4,12) B=(0,6,3) C=(3,4,6) gr 354
	cout << "Dati coordonata X a punctului A: ";
	cin >> A.x;
	cout << "Dati coordonata Y a punctului A: ";
	cin >> A.y;
	cout << "Dati coordonata Z a punctului A: ";
	cin >> A.z;
	cout << "Dati coordonata X a punctului B: ";
	cin >> B.x;
	cout << "Dati coordonata Y a punctului B: ";
	cin >> B.y;
	cout << "Dati coordonata Z a punctului B: ";
	cin >> B.z;
	cout << "Dati coordonata X a punctului C: ";
	cin >> C.x;
	cout << "Dati coordonata Y a punctului C: ";
	cin >> C.y;
	cout << "Dati coordonata Z a punctului C: ";
	cin >> C.z;

	//a) determinati un punct M in interiorul sau pe laturile triunghiului
	//M.x = (A.x + B.x + C.x)/3;
	//M.y = (A.y + B.y + C.y)/3;
	//M.z = (A.z + B.z + C.z)/3;

	M.x = A.x * 1 / 2 + B.x * 1 / 4 + C.x * 1 / 4;
	M.y = A.y * 1 / 2 + B.y * 1 / 4 + C.y * 1 / 4;
	M.z = A.z * 1 / 2 + B.z * 1 / 4 + C.z * 1 / 4;

	cout << "Punctul M(" << M.x << "," << M.y << "," << M.z << ") se afla in interiorul triunghiului si este centrul de greutate\n";

	//b) determinati D in planul triunghiului asa incat ABDC (atentie la ordine!!!) sa fie un patrulater convex
	// pentru a fi un patrulater convex trebuie ca ABDC sa fie paralelogram
	D.x = B.x + C.x - A.x;
	D.y = B.y + C.y - A.y;
	D.z = B.z + C.z - A.z;

	cout << "Punctul D(" << D.x << "," << D.y << "," << D.z << ")\n";

	//c) determinati vectorul n normal la patrulaterul ABDC
	// fiind un patrulater convex putem alege oricare 3 puncte pt calculul normalei, asa ca am ales BDC
	vectori(B, D, 0);
	vectori(D, C, 1);
	prodvect(vect[0], vect[1], 0);

	n.x = prods[0].x / sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2));
	n.y = prods[0].y / sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2));
	n.z = prods[0].z / sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2));
	
	cout << "Vectorul normal este n(" << n.x << "," << n.y << "," << n.z << ")\n";
	//d) folosind M si n construiti un punct O1 in fata patrulaterului si un punct O2 in spatele acestuia
	// pentru punctul din fata, O1, vom aduna la M un vector coliniar cu n, spre exemplu 7*sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2))*n
	/*O1.x = M.x + 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.x;
	O1.y = M.y + 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.y;
	O1.z = M.z + 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.z;
	*/
	O1.x = M.x + 15 * n.x;
	O1.y = M.y + 15 * n.y;
	O1.z = M.z + 15 * n.z;

	// pentru punctul din spate, O2, vom scadea din M un vector coliniar cu n, spre exemplu 7*sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2))*n
	/*O2.x = M.x - 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.x;
	O2.y = M.y - 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.y;
	O2.z = M.z - 2 * sqrt(pow(prods[0].x, 2) + pow(prods[0].y, 2) + pow(prods[0].z, 2)) * n.z;
	*/
	
	O2.x = M.x - 15 * n.x;
	O2.y = M.y - 15 * n.y;
	O2.z = M.z - 15 * n.z;

	cout << "Punctul din fata este O1(" << O1.x << "," << O1.y << "," << O1.z << ")\n";
	cout << "Punctul din spate este O2(" << O2.x << "," << O2.y << "," << O2.z << ")\n";

	PO0 = O1;
	Pref = M;

	vectori(PO0, Pref, 2);
	//d.x*v.x + d.y*v.y + d.z*v.z = 0
	V.x = vect[2].y;
	V.y = -vect[2].x;
	V.z = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Poligoane in context 3D. Fata si spatele unui poligon");

	init();
	glutMouseFunc(mouse2);
	glutDisplayFunc(desen2);
	glutMainLoop();
}

