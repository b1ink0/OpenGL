#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
int w = 500;
int h = 500;

void putPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawFullCircle(int xc, int yc, int x, int y)
{
    putPixel(x + xc, y + yc);
    putPixel(x + xc, -y + yc);
    putPixel(-x + xc, -y + yc);
    putPixel(-x + xc, y + yc);
    putPixel(y + xc, x + yc);
    putPixel(y + xc, -x + yc);
    putPixel(-y + xc, -x + yc);
    putPixel(-y + xc, x + yc);
}

void Bresenham()
{
    int x = 0, y, r, p, xc, yc;
    cout << "\nCenter Co-ordinate\n";
    cout << "Enter X: ";
    cin >> xc;
    cout << "Enter Y: ";
    cin >> yc;
    cout << "Enter Radius: ";
    cin >> r;
    y = r;
    p = 3 - (2 * r);
    drawFullCircle(xc, yc, x, y);
    while (x <= y)
    {
        if (p <= 0)
        {
            p = p + 4 * x + 6;
        }
        else
        {
            p = p + 4 * x - 4 * y + 10;
            y = y - 1;
        }
        x = x + 1;
        drawFullCircle(xc, yc, x, y);
    }
}

void drawAxis()
{
    glClearColor(0, 0, 0, 0);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(0, -h);
    glVertex2f(0, h);
    glColor3f(0, 1, 0);
    glVertex2f(-w, 0);
    glVertex2f(w, 0);
    glEnd();
    glFlush();
}

void display(void)
{
    drawAxis();
    glColor3f(0, 1, 1);
    Bresenham();
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Assignment 3");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}