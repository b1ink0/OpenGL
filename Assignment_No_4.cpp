#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
int w = 500;
int h = 500;

struct Color
{
    float r, g, b;
};

Color getPixelColor(int x, int y)
{
    Color color;
    try
    {
        glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, &color);
    }
    catch (string e)
    {
    }
    return color;
}

void setPixelColor(int x, int y, Color newColor)
{
    glColor3f(newColor.r, newColor.g, newColor.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void boundaryFill(int x, int y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);
    if ((color.r != oldColor.r || color.g != oldColor.g || color.b != oldColor.b) && (color.r != newColor.r || color.g != newColor.g || color.b != newColor.b))
    {
        setPixelColor(x, y, newColor);
        boundaryFill(x + 1, y, oldColor, newColor);
        boundaryFill(x, y + 1, oldColor, newColor);
        boundaryFill(x - 1, y, oldColor, newColor);
        boundaryFill(x, y - 1, oldColor, newColor);
    }
}

void floodFill(int x, int y, Color newColor)
{
    Color oldColor;
    oldColor.r = 0;
    oldColor.g = 0;
    oldColor.b = 0;
    Color color;
    color = getPixelColor(x, y);
    if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
    {
        setPixelColor(x, y, newColor);
        floodFill(x + 1, y, newColor);
        floodFill(x, y + 1, newColor);
        floodFill(x - 1, y, newColor);
        floodFill(x, y - 1, newColor);
    }
}

void drawPolygonSingleColor()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(100, 100);
    glVertex2f(100, 400);
    glVertex2f(400, 400);
    glVertex2f(400, 100);
    glEnd();
    glFlush();
}

void drawPolygonMultiColor()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f(100, 100);
    glColor3f(0, 1, 0);
    glVertex2f(100, 400);
    glColor3f(0, 0, 1);
    glVertex2f(400, 400);
    glColor3f(1, 0, 1);
    glVertex2f(400, 100);
    glEnd();
    glFlush();
}

void mouseFun(int btn, int state, int x, int y)
{
    y = w - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            Color ocolor;
            ocolor.r = 1;
            ocolor.g = 0;
            ocolor.b = 0;
            Color ncolor;
            ncolor.r = 0;
            ncolor.g = 1;
            ncolor.b = 1;
            drawPolygonSingleColor();
            boundaryFill(x, y, ocolor, ncolor);
        }
    }
    else if (btn == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            Color ncolor;
            ncolor.r = 1;
            ncolor.g = 1;
            ncolor.b = 0;
            drawPolygonMultiColor();
            floodFill(x, y, ncolor);
        }
    }
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, w, 0, h);
}

void display(void)
{
    glLineWidth(3);
    glPointSize(1);
    drawPolygonSingleColor();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Assignment 4");
    glutDisplayFunc(display);
    glutMouseFunc(mouseFun);
    myInit();
    glutMainLoop();
    return 0;
}