#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLUquadric* q = gluNewQuadric();
const float cylSlices = 50;
const float cylStacks = 50;

const float mid_Lcyl = 15;
const float mid_rcyl = 5;
const float mid_lcube = mid_Lcyl / 10.0;
const float mid_cube_err = mid_lcube / 10.0;
const float mid_rsphere = mid_lcube / 1.5;
const float mid_sphere_err = mid_rsphere / 2.0;
const float mid_elice_L = mid_Lcyl;
const float mid_elice_l = mid_rsphere * 1.3;
const float mid_elice_h = mid_rsphere / 10.0;
const float mid_feet_angle = -55;
const float mid_feet_lspace = mid_Lcyl * 0.4;
const float mid_feet_beamL = mid_feet_lspace * 0.6;
const float mid_feet_beaml = mid_feet_beamL * 0.1;
const float mid_feet_beamh = mid_feet_beaml * 0.5;

const float front_RconA = mid_rcyl;
const float front_rconA = front_RconA * 0.8;
const float front_hconA = mid_Lcyl * 0.15;
const float front_RconB = front_rconA;
const float front_rconB = front_RconB * 0.2;
const float front_hconB = front_hconA * 2;

const float back_Rcon = mid_rcyl;
const float back_rcon = back_Rcon * 0.3;
const float back_hcon = mid_Lcyl * 0.2;
const float back_rcyl = back_rcon;
const float back_hcyl = mid_Lcyl * 0.7;

const float back_elice_rcylA = back_Rcon * 0.7;
const float back_elice_hcylA = back_rcyl * 2;
const float back_elice_rcylB = back_elice_rcylA * 0.7;
const float back_elice_hcylB = back_elice_hcylA;
const float back_elice_err = back_hcyl * 0.1;
const float back_elice_rsphere = back_elice_rcylB * 0.2;

const float back_elice_beamL = back_elice_rcylB * 0.9;
const float back_elice_beaml = back_elice_rsphere;
const float back_elice_beamh = back_elice_beaml * 0.2;

const float front_hbot = front_hconA * 0.5;

float angleEliceMare = 0;
float angleEliceMica = 0;
float testangle = 0;
void CALLBACK rotleft(void)
{
	testangle += 10;
	if (testangle > 360)	testangle -= 360;
}

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

	GLfloat position[] = { 1.0, 20.0, -10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	gluQuadricNormals(q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_FALSE);
	gluQuadricOrientation(q, GLU_OUTSIDE);
	gluQuadricDrawStyle(q, GLU_FILL);
}

void draw_heli_mid_feet() {
	glPushMatrix();
		glTranslatef(-mid_feet_lspace / 2, 0, mid_feet_beamL / 2);
		auxSolidBox(mid_feet_beaml, mid_feet_beamh, mid_feet_beamL);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(mid_feet_lspace / 2, 0, mid_feet_beamL / 2);
		auxSolidBox(mid_feet_beaml, mid_feet_beamh, mid_feet_beamL);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, mid_feet_beamL + mid_feet_beaml / 2);
		glRotatef(-90, 0, 1, 0);
		auxSolidBox(mid_feet_beaml, mid_feet_beamh, mid_feet_lspace + mid_feet_beaml * 2);
	glPopMatrix();
}

void draw_heli_mid_elice() {
	glTranslatef(0,mid_lcube / 2 - mid_cube_err, 0);
	auxSolidCube(mid_lcube);
	glTranslatef(0, mid_lcube / 2 + mid_rsphere - mid_sphere_err, 0);
	auxSolidSphere(mid_rsphere);
	for (int i = 0; i < 4; i++) {
		glRotatef(90 * i, 0, 1, 0);
		glPushMatrix();
			glTranslatef(0, 0, mid_elice_L / 2);
			auxSolidBox(mid_elice_l, mid_elice_h, mid_elice_L);
		glPopMatrix();
	}
}

void draw_heli_mid() {
	glRotatef(-90, 0, 1, 0);

	glPushMatrix();
		glTranslatef(0, 0, -mid_Lcyl / 2);
		gluCylinder(q, mid_rcyl, mid_rcyl, mid_Lcyl, cylSlices, cylStacks);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, mid_rcyl, 0);
		draw_heli_mid_elice();
	glPopMatrix();

	glPushMatrix();
		glRotatef(mid_feet_angle, 0, 0, 1);
		glTranslatef(mid_rcyl, 0, 0);
		glRotatef(90, 0, 1, 0);
		draw_heli_mid_feet();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-mid_feet_angle + 180, 0, 0, 1);
		glTranslatef(mid_rcyl, 0, 0);
		glRotatef(90, 0, 1, 0);
		draw_heli_mid_feet();
	glPopMatrix();
}

void draw_heli_front() {
	glPushMatrix();
		gluCylinder(q, front_RconA, front_rconA, front_hconA, cylSlices, cylStacks);
		glTranslatef(0, 0, front_hconA);
		gluCylinder(q, front_RconB, front_rconB, front_hconB, cylSlices, cylStacks);
		glTranslatef(0, 0, front_hconB);
		auxSolidSphere(front_rconB);
	glPopMatrix();
}

void draw_heli_back_elice() {
	glPushMatrix();
		glTranslatef(0, 0, back_elice_rcylA);
		glRotatef(90, 0, 1, 0);
		glPushMatrix();
			glTranslatef(0, 0, -back_elice_hcylA / 2);
			gluCylinder(q, back_elice_rcylA, back_elice_rcylA, back_elice_hcylA, cylSlices, cylStacks);
			gluCylinder(q, back_elice_rcylB, back_elice_rcylB, back_elice_hcylB, cylSlices, cylStacks);
		glPopMatrix();
		glTranslatef(0, 0, -back_elice_hcylA / 2);
		gluDisk(q, back_elice_rcylB, back_elice_rcylA, cylSlices, cylStacks);
		glTranslatef(0, 0, back_elice_hcylA);
		gluDisk(q, back_elice_rcylB, back_elice_rcylA, cylSlices, cylStacks);
		glTranslatef(0, 0, -back_elice_hcylA / 2);
		auxSolidSphere(back_elice_rsphere);
		glRotatef(-90, 0, 1, 0);
		for (int i = 0; i < 4; i++) {
			glRotatef(90 * i, 1, 0, 0);
			glPushMatrix();
				glTranslatef(0,0, -back_elice_beamL/2);
				auxSolidBox(back_elice_beamh, back_elice_beaml, back_elice_beamL);
			glPopMatrix();
		}
	glPopMatrix();
}

void draw_heli_back() {
	glPushMatrix();
		gluCylinder(q, back_Rcon, back_rcon, back_hcon, cylSlices, cylStacks);
		glTranslatef(0, 0, back_hcon);
		gluCylinder(q, back_rcyl, back_rcyl, back_hcyl, cylSlices, cylStacks);
		glTranslatef(0, 0, back_hcyl- back_elice_err);
		draw_heli_back_elice();
	glPopMatrix();
}

void draw_heli() {
	glPushMatrix();
		draw_heli_mid();
		glTranslatef(0, 0, mid_Lcyl / 2);
		draw_heli_front();
		glTranslatef(0, 0, -mid_Lcyl);
		glRotatef(-180, 1, 0, 0);
		draw_heli_back();
	glPopMatrix();
}

void CALLBACK display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//CAMERA SETTIGNS
	glTranslatef(0, 0, -100);
	glRotatef(testangle, 0, 1, 0);
	////////////////////////////
	draw_heli();
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (GLfloat)w / (GLfloat)h, 1.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 600);
	auxInitWindow("Elicopter cepoiesc");
	myInit();
	auxReshapeFunc(myReshape);
	auxKeyFunc(AUX_LEFT, rotleft);
	auxMainLoop(display);
	return 0;
}
