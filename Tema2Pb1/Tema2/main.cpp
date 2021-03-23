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

int nrp = 4;
punct vp[4], P;

void intersectie()
{
	
	float t0, s0;
	float c1s = vp[2].x - vp[3].x;
	float c1t = vp[1].x - vp[0].x;
	float r1 = vp[2].x - vp[0].x;
	float c2s = vp[2].y - vp[3].y;
	float c2t = vp[1].y - vp[0].y;
	float r2 = vp[2].y - vp[0].y;

	// am rezolvat sistemul prin substitutie si am verificat numitorul sa fie diferit de 0 si apoi am determinat t0
	if ((c1t * c2s - c2t * c1s) == 0)
		cout << "Sistemul are in o solutie o necunoscuta care depinde de cealalta, adica avem o infinitate de solutii, lucru imposibil pentru problema noastra\n";
	else
		t0 = (r1 * c2s - r2 * c1s) / (c1t * c2s - c2t * c1s);
	
	if (t0 < 0 || t0 > 1)
		cout << "Dreptele nu se intersecteaza\n";
	else
	{
		cout << "t0 = " << t0 << "\n";
		if (c1s != 0)
		{
			s0 = (r1 - t0 * c1t) / c1s;
			if (s0 < 0 || s0 > 1)
				cout << "Dreptele nu se intersecteaza\n";
			else
			{
				cout << "s0 = " << s0 << "\n";
				P.x = (1 - t0) * vp[0].x + t0 * vp[1].x;
				P.y = (1 - t0) * vp[0].y + t0 * vp[1].y;
				cout << "Punctul de intersectie este P(" << P.x << ";" << P.y << ")\n";
			}
		}
		else
			cout << "s0 are o valoare nedeterminata";
	}
}

float necolin()
{
	// o sa verificam daca punctele C si D sunt de o parte si de alta a dreptei AB
	float a = vp[0].y - vp[1].y;
	float b = vp[1].x - vp[0].x;
	float c = vp[0].x * vp[1].y - vp[1].x * vp[0].y;
    
	float fC = a * vp[2].x + b * vp[2].y + c;
    float fD = a * vp[3].x + b * vp[3].y + c;

	return fC * fD;
}


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-5.0, 10.0, -5.0, 10.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{

	// segmentele
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.7, 0.2, 0.8);  // culoarea primului segment: rosu
	glVertex2i(vp[0].x, vp[0].y);
	glVertex2i(vp[1].x, vp[1].y);
	glColor3f(0.7, 0.9, 0.5);  // culoarea celui de-al doilea segment: verde
	glVertex2i(vp[2].x, vp[2].y);
	glVertex2i(vp[3].x, vp[3].y);
	glEnd();

	// punctul de intersectie
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.5, 0.5); // culoarea punctului de intersectie: albastru
	glVertex2i(P.x, P.y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{
	cout << "Dati coordonatele punctelor:\n";
	
	int i;
	int ok = 0;

	for (i = 0; i < nrp; i++)
		{
		 cout << "Coordonata X a punctului " << i + 1 << " este: ";
		 cin >> vp[i].x;
		 cout << "Coordonata Y a punctului " << i + 1 << " este: ";
		 cin >> vp[i].y;
		}
    
	if (necolin() < 0)
		{
		 cout << "Punctele C si D sunt deoparte si de alta a dreptei AB\n";
		 ok = 1;
		}

	if (ok == 0)
		cout << "Deoarece punctele C si D nu sunt deoparte si de alta a dreptei AB nu avem punct de intersectie";
	else
		{
		 intersectie();

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
}