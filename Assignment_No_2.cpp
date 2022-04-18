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

void DDA()
{
    float x, y, dx, dy, x1, y1, x2, y2, step;
    cout << "\nFor Bresenham\n";
    cout << "Enter x1: ";
    cin >> x1;
    cout << "Enter y1: ";
    cin >> y1;
    cout << "Enter x2: ";
    cin >> x2;
    cout << "Enter y2: ";
    cin >> y2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if (dx >= dy)
    {
        step = dx;
    }
    else
    {
        step = dy;
    }

    dx = dx / step;
    dy = dy / step;

    x = x1;
    y = y1;

    for (int i = 0; i < step; i++)
    {
        putPixel(x, y);
        x = x + dx;
        y = y + dy;
    }
}

void Bresenham()
{
    int dx, dy, p, x, y, x1, y1, x2, y2;
    cout << "\nFor DDA\n";
    cout << "Enter x1: ";
    cin >> x1;
    cout << "Enter y1: ";
    cin >> y1;
    cout << "Enter x2: ";
    cin >> x2;
    cout << "Enter y2: ";
    cin >> y2;

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    p = 2 * dy - dx;

    while (x < x2)
    {
        if (p >= 0)
        {
            putPixel(x, y);
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
        else
        {
            putPixel(x, y);
            p = p + 2 * dy;
        }
        x = x + 1;
    }
}

void drawAxis()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0, -h);
    glVertex2f(0, h);
    glVertex2f(-w, 0);
    glVertex2f(w, 0);
    glEnd();
    glFlush();
}

void reset()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
}

void menuFun(int i)
{
    switch (i)
    {
    case 0:
        reset();
        break;
    case 1:
        glColor3f(1, 0, 0);
        DDA();
        break;
    case 2:
        glColor3f(0, 1, 0);
        Bresenham();
        break;
    default:
        break;
    }
}

void display(void)
{
    drawAxis();
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
    glutCreateWindow("Assignment 2");
    glutDisplayFunc(display);

    glutCreateMenu(menuFun);
    glutAddMenuEntry("Reset", 0);
    glutAddMenuEntry("DDA", 1);
    glutAddMenuEntry("Bresenham", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    glutMainLoop();
    return 0;
}