// ComputerGraphicsP2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <gl/glut.h>
using namespace std;
GLfloat rectangle[4][3] = { { 5,0,0 },{ 5, 20, 0 },{ -5, 20, 0 },{ -5, 0, 0 } };
GLfloat borderTop[4][3] = { { 0,-2.5, 0 } ,{ 0,22.5,0 },{ -7.5, 22.5, 0 },{ -7.5, -2.5, 0 } };
GLfloat borderBot[4][3] = { { 7.5, -2.5, 0 },{ 7.5, 22.5, 0 },{ 0,22.5,0 },{ 0,-2.5, 0 } };


void draw_rectangle(void) {
	glBegin(GL_POLYGON);
	glColor3f(0.05, .31, 1.0);
	for (int i = 0; i < 4; i++)
		glVertex3fv(rectangle[i]);
	glEnd();
}

void draw_topBorder(void) {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 4; i++)
		glVertex3fv(borderTop[i]);
	glEnd();
}

void draw_botBorder(void) {
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 4; i++)
		glVertex3fv(borderBot[i]);
	glEnd();
}

void draw_topBorder2(void) {
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	for (int i = 0; i < 4; i++)
		glVertex3fv(borderTop[i]);
	glEnd();
}

void draw_botBorder2(void) {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 4; i++)
		glVertex3fv(borderBot[i]);
	glEnd();
}

void draw_ring(int i) {
	if (i % 2 == 0) {
		for (int r = 0; r < 360; r += 45) {
			glPushMatrix();
			glRotated(r, 0, 0, 1);
			glTranslated(0, 25, 0);
			draw_rectangle();
			draw_topBorder();
			draw_botBorder();
			glPopMatrix();
		}
	}
	else {

		for (int r = 0; r < 360; r += 45) {
			glPushMatrix();
			glRotated(r, 0, 0, 1);
			glTranslated(0, 25, 0);
			draw_rectangle();
			draw_topBorder2();
			draw_botBorder2();
			glPopMatrix();
		}
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslated((i + 1) * 120, 250, 0);
		draw_ring(i);
		glPopMatrix();
	}

	for (int i = 1; i < 5; i++) {
		glPushMatrix();
		glTranslated(i * 120, 100, 0);
		draw_ring(i);
		glPopMatrix();
	}

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 350);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Peripheral Drift Illusion");
	glClearColor(.82, .82, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 600, 0, 350, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutDisplayFunc(display);
	glutMainLoop();
}
