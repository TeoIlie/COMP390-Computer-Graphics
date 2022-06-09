/*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_1: 2DGraphics: Program 1

    @author: Teodor Ilie, 3564886
    @date: June 9, 2022
 
    This program draws two houses - the first without anti-aliasing, and the second with anti-aliasing.
    This is the main C++ file.
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


//draw house without anti-aliasing
void drawHouse1() {
    // draw rectangle with GL_POLYGON
    // set polygon mode to GL_LINE first
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f(-2.2f, 2.5f);
        glVertex2f(-1.7f, 0.5f);
        glVertex2f( 0.3f, 1.0f);
        glVertex2f(-0.2f, 3.0f);
    glEnd ();
    
    //draw triangle with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1.45f, 3.50f);
        glVertex2f(-2.7f, 2.36f);
        glVertex2f( 0.3f, 3.14f);
    glEnd ();
}


//draw house with anti-aliasing
void drawHouse2() {
    // enable anti-aliasing methods
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // draw rectangle with GL_POLYGON
    // set polygon mode to GL_LINE first
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f(-1.2f, -1.5f);
        glVertex2f(-0.7f, -3.5f);
        glVertex2f( 1.3f, -3.0f);
        glVertex2f( 0.8f, -1.0f);
    glEnd ();
    
    //draw triangle with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.45f, -0.50f);
        glVertex2f(-1.70f, -1.64f);
        glVertex2f( 1.30f, -0.86f);
    glEnd ();
}


// draw function for houses
void drawHouses() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear display window.
    glLoadIdentity();
    
    // view
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // set colour to black
    glColor3f(0.0, 0.0, 0.0);
    
    // draw houses
    drawHouse1();
    drawHouse2();
    
    glutSwapBuffers();
    glFlush ();
}


//reshape function
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 50.0);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main (int argc, char** argv) {
    // initialize glut
    glutInit (&argc, argv);
    
    //initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 1: Anti-aliasing");

    glutDisplayFunc(drawHouses);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
