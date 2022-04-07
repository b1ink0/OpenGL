#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

int h = 1000;
int w = 1000;
int ABC[3][2];
int ABCO[3][2];

void drawAxis()
{
    // glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0, h);
    glVertex2f(0, -h);
    glVertex2f(w, 0);
    glVertex2f(-w, 0);
    glEnd();
    glFlush();
}

void draw_orignal()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ABCO[0][0], ABCO[0][1]);
    glVertex2f(ABCO[1][0], ABCO[1][1]);
    glVertex2f(ABCO[2][0], ABCO[2][1]);
    glEnd();
    glFlush();
}

void draw(int r, int g, int b)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    draw_orignal();
    glClearColor(0, 0, 0, 0);

    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ABC[0][0], ABC[0][1]);
    glVertex2f(ABC[1][0], ABC[1][1]);
    glVertex2f(ABC[2][0], ABC[2][1]);
    glEnd();
    glFlush();
}

void translation(int tx, int ty)
{
    ABC[0][0] = ABC[0][0] + tx;
    ABC[0][1] = ABC[0][1] + ty;
    ABC[1][0] = ABC[1][0] + tx;
    ABC[1][1] = ABC[1][1] + ty;
    ABC[2][0] = ABC[2][0] + tx;
    ABC[2][1] = ABC[2][1] + ty;
    draw(0, 1, 0);
}

void scaling(float sx, float sy)
{
    ABC[0][0] = ABC[0][0] * sx;
    ABC[0][1] = ABC[0][1] * sy;
    ABC[1][0] = ABC[1][0] * sx;
    ABC[1][1] = ABC[1][1] * sy;
    ABC[2][0] = ABC[2][0] * sx;
    ABC[2][1] = ABC[2][1] * sy;
    draw(0, 0, 1);
}

void rotation(int i)
{
    float angle;
    cout << "Enter Angle In Degree: ";
    cin >> angle;
    float rad = 0.017 * angle;
    int x1 = ABC[0][0];
    int y1 = ABC[0][1];
    int x2 = ABC[1][0];
    int y2 = ABC[1][1];
    int x3 = ABC[2][0];
    int y3 = ABC[2][1];
    switch (i)
    {
    case 0:
        ABC[0][0] = x1 * cos(rad) + y1 * sin(rad);
        ABC[0][1] = y1 * cos(rad) - x1 * sin(rad);
        ABC[1][0] = x2 * cos(rad) + y2 * sin(rad);
        ABC[1][1] = y2 * cos(rad) - x2 * sin(rad);
        ABC[2][0] = x3 * cos(rad) + y3 * sin(rad);
        ABC[2][1] = y3 * cos(rad) - x3 * sin(rad);
        break;
    case 1:
        ABC[0][0] = x1 * cos(rad) - y1 * sin(rad);
        ABC[0][1] = y1 * cos(rad) + x1 * sin(rad);
        ABC[1][0] = x2 * cos(rad) - y2 * sin(rad);
        ABC[1][1] = y2 * cos(rad) + x2 * sin(rad);
        ABC[2][0] = x3 * cos(rad) - y3 * sin(rad);
        ABC[2][1] = y3 * cos(rad) + x3 * sin(rad);
        break;
    }
    draw(1, 1, 0);
}

void shearing(int i)
{
    float shx = 0, shy = 0;
    switch (i)
    {
    case 0:
        cout << "Enter X-Shear: ";
        cin >> shx;
        ABC[0][1] = ABC[0][1] + ABC[0][0] * shx;
        ABC[1][1] = ABC[1][1] + ABC[1][0] * shx;
        ABC[2][1] = ABC[2][1] + ABC[2][0] * shx;
        break;
    case 1:
        cout << "Enter Y-Shear: ";
        cin >> shy;
        ABC[0][0] = ABC[0][0] + ABC[0][1] * shy;
        ABC[1][0] = ABC[1][0] + ABC[1][1] * shy;
        ABC[2][0] = ABC[2][0] + ABC[2][1] * shy;
        break;
    default:
        break;
    }
    draw(0, 1, 1);
}

void reflection(int i)
{
    int x1 = ABC[0][0];
    int y1 = ABC[0][1];
    int x2 = ABC[1][0];
    int y2 = ABC[1][1];
    int x3 = ABC[2][0];
    int y3 = ABC[2][1];
    switch (i)
    {
    case 0:
        ABC[0][1] = -ABC[0][1];
        ABC[1][1] = -ABC[1][1];
        ABC[2][1] = -ABC[2][1];
        break;
    case 1:
        ABC[0][0] = -ABC[0][0];
        ABC[1][0] = -ABC[1][0];
        ABC[2][0] = -ABC[2][0];
        break;
    case 2:
        ABC[0][0] = y1;
        ABC[0][1] = x1;
        ABC[1][0] = y2;
        ABC[1][1] = x2;
        ABC[2][0] = y3;
        ABC[2][1] = x3;
        break;
    case 3:
        ABC[0][0] = -ABC[0][0];
        ABC[0][1] = -ABC[0][1];
        ABC[1][0] = -ABC[1][0];
        ABC[1][1] = -ABC[1][1];
        ABC[2][0] = -ABC[2][0];
        ABC[2][1] = -ABC[2][1];
        break;
    default:
        break;
    }
    draw(0, 1, 0);
}

void reset()
{
    for (int i = 0; i < 3; i++)
    {
        ABC[i][0] = ABCO[i][0];
        ABC[i][1] = ABCO[i][1];
    }
    draw(1, 0, 0);
}

void mainMenu(int i)
{
    switch (i)
    {
    case 0:
        reset();
        break;
    default:
        break;
    }
}

void translationMenuFunc(int i)
{
    int tx = 0, ty = 0;
    switch (i)
    {
    case 0:
        cout << "Enter X-Translation: ";
        cin >> tx;
        break;
    case 1:
        cout << "Enter Y-Translation: ";
        cin >> ty;
        break;
    case 2:
        cout << "Enter X-Translation: ";
        cin >> tx;
        cout << "Enter Y-Translation: ";
        cin >> ty;
    default:
        break;
    }
    translation(tx, ty);
}

void scalingMenuFunc(int i)
{
    float sx = 1, sy = 1;
    switch (i)
    {
    case 0:
        cout << "Enter X-Scaling: ";
        cin >> sx;
        break;
    case 1:
        cout << "Enter Y-Scaling: ";
        cin >> sy;
        break;
    case 2:
        cout << "Enter X-Scaling: ";
        cin >> sx;
        cout << "Enter Y-Scaling: ";
        cin >> sy;
    default:
        break;
    }
    scaling(sx, sy);
}

void rotationMenuFunc(int i)
{
    rotation(i);
}

void shearingMenuFunc(int i)
{
    shearing(i);
}

void reflectionMenuFunc(int i)
{
    reflection(i);
}

void display(void)
{
    drawAxis();
    draw_orignal();
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glPointSize(10);
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}

int main(int argc, char **argv)
{
    ABC[0][0] = 0;
    ABC[0][1] = 0;
    ABC[1][0] = 100;
    ABC[1][1] = 100;
    ABC[2][0] = 200;
    ABC[2][1] = 0;

    ABCO[0][0] = 0;
    ABCO[0][1] = 0;
    ABCO[1][0] = 100;
    ABCO[1][1] = 100;
    ABCO[2][0] = 200;
    ABCO[2][1] = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("Assignment 5");
    glutDisplayFunc(display);

    int translationMenu = glutCreateMenu(translationMenuFunc);
    glutAddMenuEntry("X-Translation", 0);
    glutAddMenuEntry("Y-Translation", 1);
    glutAddMenuEntry("X-Y-Translation", 2);

    int scalingMenu = glutCreateMenu(scalingMenuFunc);
    glutAddMenuEntry("X-Scale", 0);
    glutAddMenuEntry("Y-Scale", 1);
    glutAddMenuEntry("X-Y-Scale", 2);

    int rotationMenu = glutCreateMenu(rotationMenuFunc);
    glutAddMenuEntry("Clockwise", 0);
    glutAddMenuEntry("Anti-Clockwise", 1);

    int shearingMenu = glutCreateMenu(shearingMenuFunc);
    glutAddMenuEntry("X-Shear", 0);
    glutAddMenuEntry("Y-Shear", 1);

    int reflectionMenu = glutCreateMenu(reflectionMenuFunc);
    glutAddMenuEntry("X-Axis", 0);
    glutAddMenuEntry("Y-Axis", 1);
    glutAddMenuEntry("X=Y", 2);
    glutAddMenuEntry("Origin", 3);

    glutCreateMenu(mainMenu);

    glutAddMenuEntry("Reset Position", 0);
    glutAddSubMenu("Translation", translationMenu);
    glutAddSubMenu("Scaling", scalingMenu);
    glutAddSubMenu("Rotation", rotationMenu);
    glutAddSubMenu("Shearing", shearingMenu);
    glutAddSubMenu("Reflection", reflectionMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    myInit();
    glutMainLoop();
    return 0;
}
