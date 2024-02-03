#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <cmath>

float x1, x2, y11, y2;
int n;

struct col {
    double r, g, b;
};
col have[8] = {

    {255,255,255},{255,0,0},{0,255,0},{0,0,255},
    {255,255,0},{255,255,0},{0,255,255},
    {255,0,255}
};

int getCol(int dx,int dy){
if(abs(dx) >=abs(dy)){
if (dx >=0 and dy >=0) return 0;
if (dx <=0 and dy >=0) return 3;
if (dx <=0 and dy <=0) return 4;
if (dx >=0 and dy <=0) return 7;
}
else{
if (dx >=0 and dy >=0) return 1;
if (dx <=0 and dy >=0) return 2;
if (dx <=0 and dy <=0) return 5;
if (dx >=0 and dy <=0) return 6;


}
}

void display(void) {
    for (int i = 0; i < n; ++i) {
        float dy, dx, step, x, y, k, Xin, Yin;
        x1 = rand() % 800, x2 = rand() % 800;
        y11 = rand() % 600, y2 = rand() % 600;
        dx = x2 - x1;
        dy = y2 - y11;
        col now = have[getCol(dx, dy)];
        glColor3f(now.r, now.g, now.b);
        if (abs(dx) > abs(dy)) {
            step = abs(dx);
        }
        else
            step = abs(dy);
        Xin = dx / step;
        Yin = dy / step;
        x = x1, y = y11;
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        for (k = 1; k <= step; k++) {
            x = x + Xin;
            y = y + Yin;
            glBegin(GL_POINTS);
            glVertex2i(round(x), round(y));
            glEnd();
        }
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

int main(int argc, char** argv) {
    scanf("%d", &n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("DDA Line Drawing Algorithm with Color Zones");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
