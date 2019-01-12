// ComputerGraphicsProject1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <math.h>
#include <gl/glut.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

double t, p = 3.141593 / 180;

void drawCircle(GLfloat radius) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2d(0,0);
	int s = rand() % 2; 

	if (s == 0) {

		for (int i = 0; i <= 360; i++) {
			t = i * p;
			GLfloat shade = sin(t) * 0.5 + 0.5;
			glColor3f(shade, shade, shade);
			glVertex2d(radius * cos(t), radius *sin(t));
		}
	}
	else {
		for (int i = 0; i <= 360; i++) {
			t = i * p;
			GLfloat shade = 1 - (sin(t) * 0.5 + 0.5);
			glColor3f(shade, shade, shade);
			glVertex2d(radius * cos(t), radius *sin(t));
		}
	}

	glEnd();
}

void display(void) {
	srand(time(NULL));
	int temp = (rand() % 6) + 5;

	vector<int> xvertices(temp);
	vector<int> yvertices(temp);
	
	xvertices[0] = rand() % 700 + 75;
	yvertices[0] = rand() % 500 + 75;

	for (int i = 1; i < temp; i++) {
		int z = rand() % 700 + 75;
		for (int j = 0; j < i; j++) {
			if (abs(z - xvertices[j]) <= 35) {
				z = rand() % 700 + 75;
				j = -1;
			}
		}
		xvertices[i] = z;
	}

	for (int i = 1; i < temp; i++) {
		int z = rand() % 500 + 75;
		for (int j = 0; j < i; j++) {
			if (abs(z - yvertices[j]) <= 35) {
				z = rand() % 500 + 75;
				j = -1;
			}
		}
		yvertices[i] = z;
	}

	

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < temp; i++) {
		glPushMatrix();
		glTranslated(xvertices[i] ,yvertices[i],0);
		drawCircle(25);
		glPopMatrix();
	}

	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Project One");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glutDisplayFunc(display);
	glutMainLoop();
}

