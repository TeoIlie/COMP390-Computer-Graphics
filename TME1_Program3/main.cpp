/*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_1: 2DGraphics: Program 3

    @author: Teodor Ilie, 3564886
    @date: June 9, 2022
 
    This program draws a square with corners set to
    red, green, blue, and yellow, going clockwise
    from the bottom left.
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


// draw coloured and shaded square using GL_POLYGON
void drawSquare() {
    glBegin(GL_POLYGON);
        // set bottom left to red
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-2.5, -2.5);
    
        // set top left to green
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-2.5, 2.5);
    
        // set top right to blue
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(2.5, 2.5);
    
        // set bottom right to yellow
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(2.5, -2.5);
    glEnd();
}


// display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear display window.
    glLoadIdentity();
    
    // view
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set colour to black
    glColor3f(0.0, 0.0, 0.0);
    
    // draw square
    drawSquare();
    
    glutSwapBuffers();
    glFlush ();
}


//reshape function
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main (int argc, char** argv) {
    // initialize glut
    glutInit (&argc, argv);
    
    //initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 3: Colouring and Shading");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
