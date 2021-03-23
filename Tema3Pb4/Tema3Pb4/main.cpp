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

int n, nrv, nrpr, nrprneg, nrprpoz, pozmin, semninf;
punct vp[256], prods[256], vect[256], pinf;
int carpoi[256];

void glPrintf(int x, int y, char* sir) {
	glColor3f(1.0, 1.0, 1.0);
	
	glRasterPos2i(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*) sir);
	
}

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
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	int i;
	char sp[100];

	for (i = 1; i < n; i++)
	{
		// segmentele
		glLineWidth(5);
		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);  // culoarea primului segment: rosu
		glVertex2i(vp[i].x, vp[i].y);
		glVertex2i(vp[i + 1].x, vp[i + 1].y);
		glEnd();
	}

	// segmentele
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);  // culoarea primului segment: rosu
	glVertex2i(vp[n].x, vp[n].y);
	glVertex2i(vp[1].x, vp[1].y);
	glEnd();

	for (i = 1; i < n; i++)
	{
		//convexe
		if (carpoi[i] == semninf)
		{
			glEnable(GL_POINT_SMOOTH);
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(vp[i+1].x, vp[i+1].y);
			glEnd();
			sprintf_s(sp, "P%d", i+1);
			glPrintf(vp[i+1].x, vp[i+1].y, sp);
			glDisable(GL_POINT_SMOOTH);
		}
		//concave
		else
		{
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(0.0, 0.0, 1.0);
			glVertex2f(vp[i+1].x, vp[i+1].y);
			glEnd();
			sprintf_s(sp, "P%d", i+1);
			glPrintf(vp[i+1].x, vp[i+1].y, sp);
		}

	}

	if (carpoi[n] == semninf)
	{
		glEnable(GL_POINT_SMOOTH);
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(vp[1].x, vp[1].y);
		glEnd();
		sprintf_s(sp, "P%d", 1);
		glPrintf(vp[1].x, vp[1].y, sp);
		glDisable(GL_POINT_SMOOTH);
	}
	else
	{
		glPointSize(10);
		glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(vp[1].x, vp[1].y);
		glEnd();
		sprintf_s(sp, "P%d", 1);
		glPrintf(vp[1].x, vp[1].y, sp);
	}

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

	//carpoi este un vector caracteristic ce retine 1 pt plus, -1 pt minus
	for (i = 1; i < nrpr; i++)
	{

		if (prods[i].z < 0)
			carpoi[i] = -1;
		else
			if (prods[i].z > 0)
				carpoi[i] = 1;	
	}
	
	//carpoi este un vector caracteristic ce retine 1 pt plus, -1 pt minus
	if (prods[nrpr].z < 0)
		carpoi[nrpr] = -1;
	else
		if (prods[nrpr].z > 0)
			carpoi[nrpr] = 1;

	cout << "Produsele sunt: ";
	for (i = 1; i <= nrpr; i++)
		if (i != nrpr)
		{
			if (carpoi[i] == -1)
				cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << ")-; ";
			if (carpoi[i] == 1)
				cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << ")+; ";
		}
		else
		{
			if (carpoi[i] == -1)
				cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << ")-; ";
			if (carpoi[i] == 1)	
				cout << "(" << prods[i].x << "," << prods[i].y << "," << prods[i].z << ")+; ";
		}
	
	//o sa consideram pct-ul care are pe x coordonata minima
	pinf = vp[1];
	pozmin = 1;
	for (i = 2; i <= n; i++)
		if (vp[i].x < pinf.x)
		{
			pinf = vp[i];
			pozmin = i;
		}

	vectori(vp[(pozmin-2+n) % n+1], pinf, nrv + 1); 
	vectori(pinf, vp[(pozmin + 1) % n], nrv + 2);
	prodvect(vect[nrv + 1], vect[nrv + 2], nrpr + 1);
	
	if (prods[nrpr+1].z < 0)
		semninf = -1;
	else
		if (prods[nrpr+1].z > 0)
			semninf = 1;

	for (i = 1; i <= nrpr; i++)
		if (carpoi[i] == -1)
			nrprneg++;
		else
			nrprpoz++;

	cout << "\n" << prods[nrpr + 1].x << " " << prods[nrpr + 1].y << " " << prods[nrpr + 1].z;
	cout << "\n"<< pinf.x << " " << pinf.y << " " << pinf.z;
	cout << "\n" << semninf;
	if (nrprneg != 0 && nrprpoz != 0)
		cout << "\nPoligonul este concav";
	else
		cout << "\nPoligonul este convex";

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