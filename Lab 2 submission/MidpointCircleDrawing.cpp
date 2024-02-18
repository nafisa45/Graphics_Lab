#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace std;

int Wi = 640, He = 480;
int x = 0;
int y = 0;
int r;
// int lines;
double interval;

// ##############################Define Variables here###########################


// ##############################################################################

void myInit(void);
void display(void);
void reshape(int w, int h);
void draw_grid(void);
// ##############################Define Prototypes here###########################
int get_zone(int x_0, int y_0, int x_1, int y_1);
void drawLine_4(int x_0,int y_0, int x_1, int y_1, int zone);
//void drawline_midpoint(int x_0, int y_0, int x_1, int y_1, int zone);
void draw_vertex(int x, int y, int zone);
void draw_circle(int x, int y, int r);
void draw_line(int x_0, int y_0, int x_1, int y_1);
// ##############################################################################

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-Wi / 2, Wi / 2 - 1, -He / 2, He / 2 - 1); // size of projection plane (origin at the center)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// draws the grid
void draw_grid(void)
{
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, 239);
    glVertex2i(0, -240);
    glEnd();
}

// generates rand integers for origin and radius of circles and draws them
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.2, 0.2);

    draw_grid();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    draw_circle(x, y, r);
   

    glEnd();
    glFlush();
}



void draw_circle(int x_0, int y_0, int r)
{  
    //double interval = (double)interval;
    int lines = 360 / interval; // number of lines for one circle
   
    double degree = 0;
    int x = x_0 + r, y = y_0;

    for (int i = 0; i <= lines; i++)
    {
        draw_line(x_0, y_0, x, y);
        x = x_0 + r * cos((double)degree / 180 * 3.1416);
        y = y_0 + r * sin((double)degree / 180 * 3.1416);
        degree += interval;
    }
}


// draws line by using midpoint line drawing algorithm for zone 0 after necessary transformation
// uses different colors for different zones
void draw_line(int x_0, int y_0, int x_1, int y_1)
{

    if (get_zone(x_0,y_0,x_1,y_1) == 0){
            glColor3f(255, 255, 255);//White
            drawLine_4(-x_0,-y_0,-x_1,-y_1, 0);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 1){
            glColor3f(255, 0, 0);//Red
            drawLine_4(-y_0,-x_0,-y_1,-x_1,1);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 2){
            glColor3f(0, 255, 0);//Green
            drawLine_4(-y_0,x_0,-y_1,x_1,2);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 3){
            glColor3f(0, 0, 255);//Blue
            drawLine_4(x_0,-y_0,x_1,-y_1,3);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 4){
            glColor3f(255, 255, 0);//Yellow
            drawLine_4(x_0,y_0,x_1,y_1,4);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 5){
            glColor3f(0 ,255, 255);//Cyan
            drawLine_4(y_0,x_0,y_1,x_1,5);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 6){
            glColor3f(255, 0, 255);//Magenta
            drawLine_4(y_0,-x_0,y_1,-x_1,6);
        }
        if (get_zone(x_0,y_0,x_1,y_1) == 7){
            glColor3f(127, 127, 127);//Gray
            drawLine_4(-x_0,y_0,-x_1,y_1,7);
        }
}

void drawLine_4(int x_0,int y_0, int x_1, int y_1, int zone) {
    int dy = y_1 - y_0;
    int dx = x_1 - x_0;
    int d = -(2 * dy) + dx;
    int x = x_0;
    int y = y_0;

    draw_vertex(x,y,zone);
    
    while (x >= x_1) {
        x--;
        if (d < 0) {
            d += -(2 * dy); // delW
        } else {
            d += -2*dy+2*dx; // delWS
            y--;
        }
        draw_vertex(x,y,zone);
    }
}

//draws the pixel using 8 way symmetry
void draw_vertex(int x, int y, int zone){
    if(zone==0)
        glVertex2i(-x,-y);
    else if(zone==1)
        glVertex2i(-y,-x);
    else if(zone==2)
        glVertex2i(y,-x);
    else if(zone==3)
        glVertex2i(x,-y);
    else if(zone==4)
        glVertex2i(x,y);
    else if(zone==5)
        glVertex2i(y,x);
    else if(zone==6)
        glVertex2i(-y,x);
    else if(zone==7)
        glVertex2i(-x,y);

}

// returns the zone of a line
int get_zone(int x_0, int y_0, int x_1, int y_1)
{
    int dx = x_1 - x_0;
    int dy = y_1 - y_0;
    if (dx >= 0 && dy >= 0)
    {
        if (abs(dx) >= abs(dy))
            return 0;
        else
            return 1;
    }
    else if (dx < 0 && dy >= 0)
    {
        if (abs(dx) >= abs(dy))
            return 3;
        else
            return 2;
    }
    else if (dx < 0 && dy < 0)
    {
        if (abs(dx) >= abs(dy))
            return 4;
        else
            return 5;
    }
    else if (dx >= 0 && dy < 0)
    {
        if (abs(dx) >= abs(dy))
            return 7;
        else
            return 6;
    }
}

int main(int argc, char **argv)
{
    //srand(time(NULL));
    // #############Take Inputs###############
    printf("Enter radius : ");
    scanf("%d", &r);
    printf("Enter interval : ");
    scanf("%lf", &interval);


    // #######################################
    glutInit(&argc, argv);                                                        // to initialize the toolkit;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);                                  // sets the display mode
    glutInitWindowSize(Wi, He);                                                   // sets the window size
    glutInitWindowPosition(0, 0);                                                 // sets the starting position for the window
    glutCreateWindow("Circle Drawing using Midpoint Algorithm - 8 Way Symmetry"); // creates the window and sets the title
    myInit();                                                                     // additional initializations as necessary
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop(); // go into a loop until event occurs
    return 0;
}
