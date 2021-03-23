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
int carpoi[256], caractpunctprin[256], marcaj[256];



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
	return abs((A.x * B.y + B.x * C.y + C.x * A.y - C.x * B.y - A.x * C.y - B.x * A.y) / 2.0);
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

void deterpct()
{
	int i, j;
	float aria1, aria2, aria3, ariat;
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

	vectori(vp[(pozmin - 2 + n) % n + 1], pinf, nrv + 1);
	vectori(pinf, vp[(pozmin + 1) % n], nrv + 2);
	prodvect(vect[nrv + 1], vect[nrv + 2], nrpr + 1);

	if (prods[nrpr + 1].z < 0)
		semninf = -1;
	else
		if (prods[nrpr + 1].z > 0)
			semninf = 1;

	for (i = 1; i <= nrpr; i++)
		if (carpoi[i] == -1)
			nrprneg++;
		else
			nrprpoz++;

	cout << "\n" << prods[nrpr + 1].x << " " << prods[nrpr + 1].y << " " << prods[nrpr + 1].z;
	cout << "\n" << pinf.x << " " << pinf.y << " " << pinf.z;
	cout << "\n" << semninf;

	if (nrprneg != 0 && nrprpoz != 0)
		cout << "\nPoligonul este concav";
	else
		cout << "\nPoligonul este convex";

	for (i = 1; i <= n; i++)
		caractpunctprin[i] = 1;

	for (i = 2; i < n; i++)
		for (j = 1; j <= n; j++)
			if (j != i && j != i - 1 && j != i + 1)
			{
				aria1 = arie(vp[i - 1], vp[i], vp[j]);
				aria2 = arie(vp[i - 1], vp[j], vp[i + 1]);
				aria3 = arie(vp[j], vp[i], vp[i + 1]);
				ariat = arie(vp[i - 1], vp[i], vp[i + 1]);
				if ((aria1 + aria2 + aria3) == ariat)
				{
					caractpunctprin[i] = 0;
					break;
				}
			}

	//pt punctul P1
	for (j = 1; j <= n; j++)
		if (j != n && j != 1 && j != 2)
		{
			aria1 = arie(vp[n], vp[1], vp[j]);
			aria2 = arie(vp[n], vp[j], vp[2]);
			aria3 = arie(vp[j], vp[1], vp[2]);
			ariat = arie(vp[n], vp[1], vp[2]);
			if ((aria1 + aria2 + aria3) == ariat)
			{
				caractpunctprin[1] = 0;
				break;
			}
		}

	//pt punctul Pn
	for (j = 1; j <= n; j++)
		if (j != n - 1 && j != n && j != 1)
		{
			aria1 = arie(vp[n - 1], vp[n], vp[j]);
			aria2 = arie(vp[n - 1], vp[j], vp[1]);
			aria3 = arie(vp[j], vp[n], vp[1]);
			ariat = arie(vp[n - 1], vp[n], vp[1]);
			if ((aria1 + aria2 + aria3) == ariat)
			{
				caractpunctprin[n] = 0;
				break;
			}
		}

}

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen(void) // procedura desenare  
{
	int i,j;

	for (i = 1; i < n; i++)
	{
		// segmentele
		glLineWidth(5);
		glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(vp[i].x, vp[i].y);
		glVertex2i(vp[i + 1].x, vp[i + 1].y);
		glEnd();
	}

	// segmentele
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(vp[n].x, vp[n].y);
	glVertex2i(vp[1].x, vp[1].y);
	glEnd();

	while (n > 2)
	{
		for (i = 1; i < n; i++)
		{
			if (carpoi[i] == semninf && caractpunctprin[i + 1] == 1)
			{
				glLineWidth(10);
				glBegin(GL_POLYGON);
				glColor3f((rand() % 256) * 1.0 / 256, (rand() % 256) * 1.0 / 256, (rand() % 256) * 1.0 / 256);
				glVertex2f(vp[i].x, vp[i].y);
				glVertex2f(vp[i+1].x, vp[i+1].y);
				glVertex2f(vp[(i + 1)%n+1].x, vp[(i + 1)%n+1].y);
				glEnd();
				for (j = i + 2; j <= n; j++)
				{
					vp[j - 1] = vp[j];
				}
				n--;
				deterpct();
				break;
			}
		}
		if (carpoi[n] == semninf && caractpunctprin[1] == 1)
		{
			glLineWidth(10);
			glBegin(GL_POLYGON);
			glColor3f((rand() % 256) * 1.0 / 256, (rand() % 256) * 1.0 / 256, (rand() % 256) * 1.0 / 256);
			glVertex2f(vp[n].x, vp[n].y);
			glVertex2f(vp[1].x, vp[1].y);
			glVertex2f(vp[2].x, vp[2].y);
			glEnd();
			for(j=2;j<=n;j++)
				vp[j - 1] = vp[j];
			n--;
			deterpct();
		}
	}
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

void main(int argc, char** argv)
{

	cout << "Dati numarul de puncte: ";
	cin >> n;

	cout << "Dati coordonatele punctelor:\n";

	int i, j;
	float aria1, aria2, aria3, ariat;

	for (i = 1; i <= n; i++)
	{
		cout << "Coordonata X a punctului " << i << " este: ";
		cin >> vp[i].x;
		cout << "Coordonata Y a punctului " << i << " este: ";
		cin >> vp[i].y;
		cout << "Coordonata Z a punctului " << i << " este: ";
		cin >> vp[i].z;
	}

	deterpct();
	cout << "\nCaracteristici: \n";
	for (i = 1; i <= n; i++)
		cout << carpoi[i] << " " << caractpunctprin[i] << "\n";

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