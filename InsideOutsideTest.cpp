// ComputerGraphicsP3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <gl/glut.h>
#include <cmath>
#include <math.h>


using namespace std;

GLint vert[100][2];
GLint points[100][2];

int width = 400, height = 600, n = 0,
type = GL_LINE_STRIP, v, p;
bool rubberbanding = false, antialiasing = false;
bool cPressed = false;
int m = 0;

double getAngle(double x1, double y1, double x2, double y2) {
	double twoPi = 2 * M_PI;
	double dtheta, theta1, theta2;

	theta1 = atan2(y1, x1);
	theta2 = atan2(y2, x2);
	dtheta = theta2 - theta1;

	while (dtheta > M_PI)
		dtheta -= twoPi;
	while (dtheta < -M_PI)
		dtheta += twoPi;

	return dtheta;
}

bool insideOutsideTest(int a) {
	double angle = 0;
	double p1x, p1y, p2x, p2y;

	for (int i = 0; i < n; i++) {
		p1x = vert[i][0] - points[a][0];
		p1y = vert[i][1] - points[a][1];
		p2x = vert[(i+1) % n][0] - points[a][0];
		p2y = vert[(i + 1) % n][1] - points[a][1];
		angle += getAngle(p1x, p1y, p2x, p2y);
	}
	if (abs(angle) < M_PI)
		return false;
	else return true;
}


void draw_inside(int a) {
	glBegin(GL_POINTS);
	glColor3f(0, 1, 0);
	glVertex2iv(points[a]);
	glEnd();
}

void draw_outside(int a) {
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2iv(points[a]);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 0);
	glBegin(cPressed ? GL_LINE_LOOP : GL_LINE_STRIP);
	for (int i = 0; i < n; i++)
		glVertex2iv(vert[i]);
	glEnd();

	for (int i = 0; i < m; i++) {
		if (insideOutsideTest(i)) {
			draw_inside(i);
		}else draw_outside(i);
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a': antialiasing = !antialiasing;
		if (antialiasing) {
			glEnable(GL_BLEND);
			glEnable(GL_LINE_SMOOTH);
		}
		else {
			glDisable(GL_BLEND);
			glDisable(GL_LINE_SMOOTH);
		}
		break;
	case 'r': n = 0; m = 0; cPressed = false; break;
	case 'c': type = GL_LINE_LOOP; cPressed = true; break;
	}

	glutPostRedisplay();
}

int findVertex(int x, int y) {
	int dx, dy;
	for (int i = 0; i < n; i++) {
		dx = vert[i][0] - x;
		dy = vert[i][1] - y;
		if (dx*dx + dy * dy < 16) return i;
	}
	return -1;
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			if (!cPressed && n < 100) {
				v = n++;
				vert[v][0] = x;
				vert[v][1] = height - 1 - y;
				rubberbanding = true;
				glutPostRedisplay();
			}
			else if(cPressed && m < 100){
				p = m++;
				points[p][0] = x;
				points[p][1] = height - 1 - y;
				rubberbanding = false;
				glutPostRedisplay();
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN && (v = findVertex(x, height - 1 - y)) != -1) {
			if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
				for (int i = v; i < n - 1; i++) {
					vert[i][0] = vert[i + 1][0];
					vert[i][1] = vert[i + 1][1];
				}
				n--;
			}
			else {
				vert[v][0] = x;
				vert[v][1] = height - 1 - y;
				rubberbanding = true;
			}
			glutPostRedisplay();
		}
		else rubberbanding = false;
		break;
	}
}

void motion(int x, int y) {
	if (rubberbanding) {
		vert[v][0] = x;
		vert[v][1] = height - 1 - y;
		glutPostRedisplay();
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("Project 3: Inside Outside Test");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();

}

