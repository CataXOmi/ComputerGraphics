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

punct A, B, C, M;

float necolin(punct A, punct B, punct C)
{
	// construim dreapta
	float a = A.y - B.y;
	float b = B.x - A.x;
	float c = A.x * B.y - B.x * A.y;

	float fC = a * C.x + b * C.y + c;
	
	return fC;
}

float arie(punct A, punct B, punct C)
{
	return abs((A.x * B.y + B.x * C.y + C.x * A.y - C.x * B.y - A.x * C.y - B.x * A.y)/2.0);
}


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-5.0, 10.0, -5.0, 10.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glLineWidth(10);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);  // culoarea primului segment: rosu
	glVertex2i(A.x, A.y);
	glVertex2i(B.x, B.y);
	glVertex2i(C.x, C.y);
	glEnd();

	// punctul de intersectie
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0); // culoarea punctului de intersectie: albastru
	glVertex2i(M.x, M.y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	float aria1, aria2, aria3, ariat;

	cout << "Dati coordonata X a punctului A: ";
	cin >> A.x;
	cout << "Dati coordonata Y a punctului A: ";
	cin >> A.y;
	cout << "Dati coordonata X a punctului B: ";
	cin >> B.x;
	cout << "Dati coordonata Y a punctului B: ";
	cin >> B.y;
	cout << "Dati coordonata X a punctului C: ";
	cin >> C.x;
	cout << "Dati coordonata Y a punctului C: ";
	cin >> C.y;
	cout << "Dati coordonata X a punctului M: ";
	cin >> M.x;
	cout << "Dati coordonata Y a punctului M: ";
	cin >> M.y;

	if (necolin(A,B,C) != 0)
	{
		cout << "Punctele A,B,C sunt necoliniare\n";
	}
	else
		cout << "Punctele A,B,C sunt coliniare\n";
	
	aria1 = arie(A, B, M);
	aria2 = arie(A, M, C);
	aria3 = arie(M, B, C);
	ariat = arie(A, B, C);

	cout << aria1 << "\n";
	cout << aria2 << "\n";
	cout << aria3 << "\n";
	cout << ariat << "\n";

	if ((aria1 + aria2 + aria3) == ariat)
	{
		if (necolin(A, B, M) == 0)
			cout << "Punctul M(" << M.x << "," << M.y << ") este in interior si se afla pe latura AB a triunghiului\n";
		if (necolin(A, C, M) == 0)
			cout << "Punctul M(" << M.x << "," << M.y << ") este in interior si se afla pe latura AC a triunghiului\n";
		if (necolin(B, C, M) == 0)
			cout << "Punctul M(" << M.x << "," << M.y << ") este in interior si se afla pe latura BC a triunghiului\n";
		else
			cout << "Punctul M(" << M.x << "," << M.y << ") este in interiorul triunghiului, dar nu pe laturi";
	}
	else
		cout << "Punctul M(" << M.x << "," << M.y << ") este in exteriorul triunghiului";

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