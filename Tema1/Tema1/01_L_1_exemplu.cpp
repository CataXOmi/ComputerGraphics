#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)


void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(0.1, 0.2, 0.5, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 1080.0, 0.0, 720.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void desen(void) // procedura desenare  
{

	// segmentele
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(0.7, 0.2, 0.8);  // culoarea primului segment: rosu
	glVertex2i(0, 720);
	glVertex2i(1080, 0);
	glColor3f(0.7, 0.9, 0.5);  // culoarea celui de-al doilea segment: verde
	glVertex2i(0, 0);
	glVertex2i(1080, 720);
	glEnd();

	// punctul de intersectie
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.5, 0.5); // culoarea punctului de intersectie: albastru
	glVertex2i(540, 360);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}
void main(int argc, char** argv)
{
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