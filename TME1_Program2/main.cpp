/*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_1: 2DGraphics: Program 2

    @author: Teodor Ilie, 3564886
    @date: June 9, 2022
 
    This program draws 5 houses using a single draw_house function,
    by the use of OpenGL matrix  rotation and translation functions.
*/

#include <stdlib.h>
#include <fstream>
#include <iostream>

// if platform is Windows
#ifdef WIN32
#include <windows.h>
#endif

// if platform is Mac
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


// initialize the display
void initDisplay(int width, int height, std::string title) {
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    const char *display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);
    
    glClearColor (1.0, 1.0, 1.0, 0.0); // set background color to white.
}


//draw_house draws the center house
void draw_house(){
    // enable anti-aliasing methods
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // set color to black
    glColor3f(0.0, 0.0, 0.0);
    
    // draw rectangle with GL_POLYGON
    // set polygon mode to GL_LINE first
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f (0.5,1.5);
        glVertex2f (0.5,0.5);
        glVertex2f (-0.5,0.5);
        glVertex2f (-0.5,1.5);
    glEnd ();
    
    //draw triangle with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glVertex2f (0,2);
        glVertex2f (0.75,1.5);
        glVertex2f (-0.75,1.5);
    glEnd ();
}


// display method shows 5 rotated houses
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //draw center house
    draw_house();
    
    //draw subsequent houses using rotation and translation matrices
    
    //leftmost
    glPushMatrix();
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glTranslatef(-3., 1., 0.0);
    draw_house();
    glPopMatrix();
    
    //left of center
    glPushMatrix();
    glRotatef(20.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.5, 0.25, 0.0);
    draw_house();
    glPopMatrix();
    
    //right of center
    glPushMatrix();
    glRotatef(-20.0, 0.0, 0.0, 1.0);
    glTranslatef(1.5, 0.25, 0.0);
    draw_house();
    glPopMatrix();
    
    //rightmost
    glPushMatrix();
    glRotatef(-40.0, 0.0, 0.0, 1.0);
    glTranslatef(3., 1, 0.0);
    draw_house();
    glPopMatrix();
    
    glutSwapBuffers();
    glFlush ();
}


// reshape method
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main(int argc, char **argv){
    // initialize GLUT
    glutInit (&argc, argv);
    
    //initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 2: 2D Graphics Transformation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
