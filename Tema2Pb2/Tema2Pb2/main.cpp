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

int n;
punct vp[256], P[256][256];
bool Pb[256][256];
bool ok[256];

typedef struct muchie
{
	punct A;
	punct B;
};

int nrm;
muchie vm[256];
int nrp;

void intersectie()
{
	int i, j;
	float t0 = 0, s0 = 0;

	for (i = 1; i < nrm; i++)
		for (j = 0; j < i; j++) // cand apare o muchie noua se test
		{

			float c1s = vm[i].A.x - vm[i].B.x;//xc-xd
			float c1t = vm[j].B.x - vm[j].A.x;//xb-xa
			float r1 = vm[i].A.x - vm[j].A.x;//xc-xa
			float c2s = vm[i].A.y - vm[i].B.y;//yc-yd
			float c2t = vm[j].B.y - vm[j].A.y;//yb-ya
			float r2 = vm[i].A.y - vm[j].A.y;//yc-ya

			// am rezolvat sistemul prin substitutie si am verificat numitorul sa fie diferit de 0 si apoi am determinat t0
			if ((c1t * c2s - c2t * c1s) == 0)
				cout << "Sistemul are in o solutie o necunoscuta care depinde de cealalta, adica avem o infinitate de solutii, lucru imposibil pentru problema noastra\n";
			else
				t0 = (r1 * c2s - r2 * c1s) / (c1t * c2s - c2t * c1s);

			if (t0 <= 0 || t0 >= 1)
				cout << "Dreptele nu se intersecteaza t0=" << t0 << "\n";
			else
			{
				cout << "t0 = " << t0 << "\n";
				if (c1s != 0)
				{
					s0 = (r1 - t0 * c1t) / c1s;
					if (s0 <= 0 || s0 >= 1)
						cout << "Dreptele nu se intersecteaza s0=" << s0 << "\n";
					else
					{
						cout << "s0 = " << s0 << "\n";
						P[i][j].x = (1 - t0) * vm[j].A.x + t0 * vm[j].B.x;
						P[i][j].y = (1 - t0) * vm[j].A.y + t0 * vm[j].B.y;
						Pb[i][j] = 1;
						cout << "Punctul de intersectie este P(" << P[i][j].x << ";" << P[i][j].y << ")\n";
						nrp++;
						ok[i] = 1;
						ok[j] = 1;
					}
				}
				else
					cout << "s0 are o valoare nedeterminata\n";
			}
		}
}


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-5.0, 10.0, -5.0, 10.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	int i,j;
	glLineWidth(10);
	glLineStipple(1, 0x00FF);
	//glBegin(GL_LINES);
	for (i = 0; i < nrm; i++)
	{	// segmentele

		if (ok[i] == 0)
			glColor3f(0, 1, 0);
		else
		{
			
			glColor3f(1, 0, 0);
			glEnable(GL_LINE_STIPPLE);
		}
		glBegin(GL_LINES);
		glVertex2i(vm[i].A.x, vm[i].A.y);
		glVertex2i(vm[i].B.x, vm[i].B.y);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}
	//glEnd();
	
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	for (i=0;i<256;i++)
		for (j=0;j<256;j++)
			if (Pb[i][j] == 1)
			{
				glColor3f(0, 0, 1);
				glVertex2f(P[i][j].x, P[i][j].y);
			}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush();
}

void main(int argc, char** argv)
{
	cout << "Dati numarul de puncte: ";
	cin >> n;

	cout << "Dati coordonatele punctelor:\n";

	int i;

	for (i = 0; i < n; i++)
	{
		cout << "Coordonata X a punctului " << i + 1 << " este: ";
		cin >> vp[i].x;
		cout << "Coordonata Y a punctului " << i + 1 << " este: ";
		cin >> vp[i].y;
	}

	for (i = 0; i < n-1; i++)
	{
		vm[i].A.x = vp[i].x;
		vm[i].A.y = vp[i].y;
		vm[i].B.x = vp[i + 1].x;
		cout << vm[i].B.x << "\n";
		vm[i].B.y = vp[i + 1].y;
		cout << vm[i].B.y << "\n";

		nrm+=1;
	}

	for (i = 0; i < nrm; i++)
	{
		cout << "A: "<< vm[i].A.x << " " << vm[i].A.y << "\n";
		cout << "B: "<< vm[i].B.x << " " << vm[i].B.y << "\n";
	}

	intersectie();

	for (i = 0; i < nrm; i++)
	{
		cout << ok[i] << "\n";
	}

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