#include <iostream>
#include <queue>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define ROUND(X) ((int)X + 0.5)
int w = 500;
int h = 500;

void DDA(float x1, float y1, float x2, float y2)
{
    float steps, dx, dy, xi, yi, x, y;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) >= abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    xi = dx / steps;
    yi = dy / steps;

    x = x1;
    y = y1;
    glBegin(GL_POINTS);
    glVertex2f(ROUND(x), ROUND(y));
    glEnd();
    for (int i = 0; i < steps; i++)
    {
        glBegin(GL_POINTS);
        glVertex2f(ROUND(x), ROUND(y));
        glEnd();
        x = x + xi;
        y = y + yi;
        glFlush();
    }
}

void DDA_dashed(float x1, float y1, float x2, float y2)
{
    float x, y, dx, dy, steps, xi, yi;
    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xi = dx / steps;
    yi = dy / steps;

    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    int count = 1;
    for (int i = 0; i < steps; i++)
    {
        if (count <= 10)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            x = xi + x;
            y = yi + y;
            glFlush();
            count++;
        }
        if (count >= 10)
        {
            x = xi + x;
            y = yi + y;
            count++;
            if (count == 20)
            {
                count = 1;
            }
        }
    }
}

void DDA_dotted(float x1, float y1, float x2, float y2)
{
    float x, y, dx, dy, xi, yi, steps;
    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xi = dx / steps;
    yi = dy / steps;

    x = x1;
    y = y1;
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    int count = 1;
    for (int i = 0; i < steps; i++)
    {
        x = x + xi;
        y = y + yi;
        if (count % 10 == 0)
        {
            glBegin(GL_POINTS);
            glVertex2f(x, y);
            glEnd();
            glFlush();
        }
        count++;
    }
}

void BH_simple(int x1, int y1, int x2, int y2)
{
    float dx, dy, x, y, g;
    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    if (dy / dx < 1)
    {
        g = 2 * dy - dx;
        while (x < x2)
        {
            x++;
            if (g >= 0)
            {
                y++;
                g = g + 2 * (dy - dx);
            }
            else
            {
                g = g + 2 * dy;
            }
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
    }
    else
    {
        g = 2 * dx - dy;
        while (y < y2)
        {
            y++;
            if (g >= 0)
            {
                x++;
                g = g + 2 * (dx - dy);
            }
            else
            {
                g = g + 2 * dx;
            }
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
    }
}

void BH_dashed(int x1, int y1, int x2, int y2)
{
    int dx, dy, x, y, g;
    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    // if (dy / dx < 1)
    // {
    int count = 1;
    g = 2 * dy - dx;
    while (x <= x2)
    {
        x++;
        if (g >= 0)
        {
            y++;
            g = g + 2 * (dy - dx);
        }
        else
        {
            g = g + 2 * dy;
        }
        if (count <= 10)
        {
            count++;
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
        if (count >= 10)
        {
            count++;
            if (count == 20)
            {
                count = 1;
            }
        }
    }
    // }
}

void BH_dotted(int x1, int y1, int x2, int y2)
{
    int dx, dy, x, y, g;
    dx = x2 - x1;
    dy = y2 - y1;
    g = 2 * dy - dx;
    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    int count = 1;
    while (x <= x2)
    {
        x++;
        if (g >= 0)
        {
            y++;
            g = g + 2 * (dy - dx);
        }
        else
        {
            g = g + 2 * dy;
        }
        if (count % 10 == 0)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
        }
        count++;
    }
}

void put_pixel(int x, int y)
{
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void draw_circle(int xc, int yc, int x, int y)
{
    put_pixel(x + xc, y + yc);
    put_pixel(-x + xc, y + yc);
    put_pixel(x + xc, -y + yc);
    put_pixel(-x + xc, -y + yc);
    put_pixel(y + xc, x + yc);
    put_pixel(-y + xc, x + yc);
    put_pixel(y + xc, -x + yc);
    put_pixel(-y + xc, -x + yc);
}

void BH_Circle(int xc, int yc, int r)
{
    float x, y, s;
    x = 0;
    y = r;

    s = 3 - 2 * r;

    while (x < y)
    {
        draw_circle(xc, yc, x, y);
        if (s <= 0)
        {
            s = s + 4 * x + 6;
            x++;
        }
        else
        {
            s = s + 4 * (x - y) + 10;
            x++;
            y--;
        }
    }
}

struct Color
{
    float r, g, b;
};
struct XY
{
    int x, y;
};

void put_pixels(int x, int y, Color NC)
{
    glColor3f(NC.r, NC.g, NC.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

Color get_color(int x, int y)
{
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void flood_fill(int x, int y, Color NC, Color OC)
{
    Color color;
    XY xy_1, xy_2;
    xy_1.x = x;
    xy_1.y = y;
    queue<XY> q;
    q.push(xy_1);
    while (!q.empty())
    {
        xy_1 = q.front();
        color = get_color(xy_1.x, xy_1.y);
        if (color.r == OC.r && color.g == OC.g && color.b == OC.b)
        {
            put_pixels(xy_1.x, xy_1.y, NC);
            xy_2.x = xy_1.x + 1;
            xy_2.y = xy_1.y;
            q.push(xy_2);
            xy_2.x = xy_1.x;
            xy_2.y = xy_1.y + 1;
            q.push(xy_2);
            xy_2.x = xy_1.x - 1;
            xy_2.y = xy_1.y;
            q.push(xy_2);
            xy_2.x = xy_1.x;
            xy_2.y = xy_1.y - 1;
            q.push(xy_2);
        }
        q.pop();
    }
}

void display(void)
{
    glBegin(GL_LINES);
    glVertex2f(-w / 2, 0);
    glVertex2f(w / 2, 0);
    glVertex2f(0, -h / 2);
    glVertex2f(0, h / 2);
    glEnd();
    glFlush();
    // BH_Circle(0, 0, 30);
}

void myInit()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
    // gluOrtho2D(0, w, 0, h);
    glPointSize(2);
}

void menu(int i)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-w / 2, 0);
    glVertex2f(w / 2, 0);
    glVertex2f(0, -h / 2);
    glVertex2f(0, h / 2);
    glEnd();
    glFlush();
    switch (i)
    {
    case 0:
        DDA(0, 0, 100, 250);
        break;
    case 1:
        DDA_dashed(0, 0, 100, 250);
        break;
    case 2:
        DDA_dotted(0, 0, 100, 250);
        break;
    case 3:
        BH_simple(0, 0, 100, 250);
        break;
    case 4:
        BH_dashed(0, 0, 250, 100);
        break;
    case 5:
        BH_dotted(0, 0, 250, 100);
        break;
    default:
        break;
    }
}

void dda_menu(int i)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-w / 2, 0);
    glVertex2f(w / 2, 0);
    glVertex2f(0, -h / 2);
    glVertex2f(0, h / 2);
    glEnd();
    glFlush();
    switch (i)
    {
    case 0:
        DDA(0, 0, 100, 250);
        break;
    case 1:
        DDA_dashed(0, 0, 100, 250);
        break;
    case 2:
        DDA_dotted(0, 0, 100, 250);
        break;
    default:
        break;
    }
}

void bh_menu(int i)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(-w / 2, 0);
    glVertex2f(w / 2, 0);
    glVertex2f(0, -h / 2);
    glVertex2f(0, h / 2);
    glEnd();
    glFlush();
    switch (i)
    {
    case 0:
        BH_simple(0, 0, 100, 250);
        break;
    case 1:
        BH_dashed(0, 0, 250, 100);
        break;
    case 2:
        BH_dotted(0, 0, 250, 100);
        break;
    default:
        break;
    }
}

void mouse(int btn, int state, int x, int y)
{
    y = w - y;
    if (btn == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            BH_Circle(x, y, 30);
            Color NC, OC;
            NC.r = 1;
            NC.g = 0;
            NC.b = 0;
            OC.r = 0;
            OC.g = 0;
            OC.b = 0;
            flood_fill(x, y, NC, OC);
        }
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(w, h);
    glutCreateWindow("ahhhhh");
    int dda = glutCreateMenu(dda_menu);
    glutAddMenuEntry("DDA Simple", 0);
    glutAddMenuEntry("DDA Dashed", 1);
    glutAddMenuEntry("DDA Dotted", 2);
    int bh = glutCreateMenu(bh_menu);
    glutAddMenuEntry("BH Simple", 0);
    glutAddMenuEntry("BH Dashed", 1);
    glutAddMenuEntry("BH Dotted", 2);
    glutCreateMenu(menu);
    glutAddSubMenu("DDA", dda);
    glutAddSubMenu("BH", bh);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
    return 0;
}