#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
int w = 500;
int h = 500;

double randd()
{
    return (double)rand() / (RAND_MAX + 1.0);
}

void koch(int x1, int y1, int x2, int y2, int n)
{
    int mat[5][2], dx, dy;
    dx = (x2 - x1) / 3;
    dy = (y2 - y1) / 3;

    mat[0][0] = x1;
    mat[0][1] = y1;

    mat[4][0] = x2;
    mat[4][1] = y2;

    mat[1][0] = x1 + dx;
    mat[1][1] = y1 + dy;

    mat[3][0] = x1 + 2 * dx;
    mat[3][1] = y1 + 2 * dy;

    mat[2][0] = (mat[1][0] + mat[3][0] - sqrt(3) * (mat[3][1] - mat[1][1])) / 2;
    mat[2][1] = (mat[1][1] + mat[3][1] + sqrt(3) * (mat[3][0] - mat[1][0])) / 2;

    if (n > 0)
    {
        koch(mat[0][0], mat[0][1], mat[1][0], mat[1][1], n - 1);
        koch(mat[1][0], mat[1][1], mat[2][0], mat[2][1], n - 1);
        koch(mat[2][0], mat[2][1], mat[3][0], mat[3][1], n - 1);
        koch(mat[3][0], mat[3][1], mat[4][0], mat[4][1], n - 1);
    }
    else
    {
        glColor3f(randd(), randd(), randd());
        glBegin(GL_LINES);
        glVertex2d(mat[0][0], mat[0][1]);
        glVertex2d(mat[1][0], mat[1][1]);

        glVertex2d(mat[1][0], mat[1][1]);
        glVertex2d(mat[2][0], mat[2][1]);

        glVertex2d(mat[2][0], mat[2][1]);
        glVertex2d(mat[3][0], mat[3][1]);

        glVertex2d(mat[3][0], mat[3][1]);
        glVertex2d(mat[4][0], mat[4][1]);
        glEnd();
        glFlush();
    }
}

void display(void)
{
    koch(0, 250, 500, 250, 2);
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    gluOrtho2D(0, w, 0, h);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("New");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}