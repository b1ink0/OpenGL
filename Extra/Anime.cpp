#include <iostream>
#include <GL/glut.h>
using namespace std;

int w = 500, h = 500;
int x = 10, y = 250;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glutSwapBuffers();
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, w, 0, h);
    glPointSize(20);
}
int flag = 1;
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    int speed = 2;
    if (flag)
    {
        x = x + speed;
    }
    else
    {
        x = x - speed;
    }
    if (x > 490)
    {
        flag = 0;
    }
    if (x < 10)
    {
        flag = 1;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("ahhhh");
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    myInit();
    glutMainLoop();
}