#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>

#define WIDTH 800
#define HEIGHT 600

int RADIUS;
int DEGREE_BETWEEN_LINES;

void drawLineDDA(int x0, int y0, int x1, int y1);
void drawPixel(int x, int y, int zone);
int getCol(int dx, int dy);

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH / 2, WIDTH / 2 - 1, -HEIGHT / 2, HEIGHT / 2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int points[360][4];

void generateLines()
{
    for (int i = 0; i < 360; i += DEGREE_BETWEEN_LINES)
    {
        points[i][0] = 0;
        points[i][1] = 0;
        points[i][2] = RADIUS * cos(i * M_PI / 180.0);
        points[i][3] = RADIUS * sin(i * M_PI / 180.0);
    }
}

void drawLineDDA(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x0;
    float y = y0;

    int zone = getCol(dx, dy);

    for (int i = 0; i <= steps; i++)
    {
        drawPixel(round(x), round(y), zone);
        x += xIncrement;
        y += yIncrement;
    }
}

void drawPixel(int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glColor3ub(255, 255, 255); // White
        break;
    case 1:
        glColor3ub(255, 0, 0); // Red
        break;
    case 2:
        glColor3ub(0, 255, 0); // Green
        break;
    case 3:
        glColor3ub(0, 0, 255); // Blue
        break;
    case 4:
        glColor3ub(255, 255, 0); // Yellow
        break;
    case 5:
        glColor3ub(0, 255, 255); // Magenta
        break;
    case 6:
        glColor3ub(255, 0, 255); // Cyan
        break;
    case 7:
        glColor3ub(127, 127, 127); // Dark Gray
        break;
    
    default:
        break;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int getCol(int dx, int dy)
{
    if (abs(dx) >= abs(dy))
    {
        if (dx >= 0 && dy >= 0)
            return 0;
        if (dx <= 0 && dy >= 0)
            return 3;
        if (dx <= 0 && dy <= 0)
            return 4;
        if (dx >= 0 && dy <= 0)
            return 7;
    }
    else
    {
        if (dx >= 0 && dy >= 0)
            return 1;
        if (dx <= 0 && dy >= 0)
            return 2;
        if (dx <= 0 && dy <= 0)
            return 5;
        if (dx >= 0 && dy <= 0)
            return 6;
    }

    return -1; // Invalid zone
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH / 2, 0);
    glVertex2i(WIDTH / 2, 0);
    glVertex2i(0, -HEIGHT / 2);
    glVertex2i(0, HEIGHT / 2);
    glEnd();

    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < 360; i += DEGREE_BETWEEN_LINES)
        drawLineDDA(points[i][0], points[i][1], points[i][2], points[i][3]);

    glEnd();

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    printf("Enter the radius of the circle: ");
    scanf("%d", &RADIUS);

    printf("Enter the degree between two lines: ");
    scanf("%d", &DEGREE_BETWEEN_LINES);

    generateLines();

    glutCreateWindow("Experiment 02");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

