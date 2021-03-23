#include<windows.h>
#include<GL/glew.h>
#include<gl/freeglut.h>
#include<iostream>

using namespace std;

typedef struct punct
{
	float x;
	float y;
	float z;
};

int n,nrv,nrpr;
punct vp[256], prods[256], vect[256];

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


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-5.0, 10.0, -5.0, 10.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	int i;

	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 1.0); 
	for (i = 1; i <= n; i++)
		glVertex2f(vp[i].x, vp[i].y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	
	cout << "Dati numarul de puncte: ";
	cin >> n;

	cout << "Dati coordonatele punctelor:\n";

	int i;

	for (i = 1; i <= n; i++)
	{
		cout << "Coordonata X a punctului " << i << " este: ";
		cin >> vp[i].x;
		cout << "Coordonata Y a punctului " << i << " este: ";
		cin >> vp[i].y;
		cout << "Coordonata Z a punctului " << i << " este: ";
		cin >> vp[i].z;
	}

	//am considerat vectorii astfel: P1P2,P2P3,P3P4,...,Pn-1Pn,PnP1
	for (i = 1; i < n; i++)
	{
		vectori(vp[i], vp[i + 1], i);
		nrv++;
	}
	vectori(vp[n], vp[1], n);
	nrv++;

	for (i = 1; i < nrv; i++)
	{
		prodvect(vect[i], vect[i + 1], i);
		nrpr++;
	}

	prodvect(vect[nrv], vect[1], nrv);
	nrpr++;

	cout << "Produsele sunt: ";
	for (i = 1; i <= nrpr; i++)
		if (i!=nrpr)
			cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << "); ";
		else
			cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << ")";

	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(75, 50); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(1080, 720); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	
}