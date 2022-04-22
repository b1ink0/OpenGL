#include <iostream>
#include <GL/glut.h>
using namespace std;
int w = 500;
int h = 500;

void display(void)
{
    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2d(w / 2, h / 2);
    glEnd();
    glFlush();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, w, 0, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Assignment 1");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}