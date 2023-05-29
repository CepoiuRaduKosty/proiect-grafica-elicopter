#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"

void myInit()
{
	//se fac setarile pentru iluminare 
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 0.15 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
	GLfloat mat_shininess[] = { 15.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat position[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_DEPTH_TEST);
}

void CALLBACK display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	


	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Elicopter cepoiesc");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
