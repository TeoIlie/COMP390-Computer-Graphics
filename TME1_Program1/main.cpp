//  main.cpp
//  TME_1_2DGraphics: Program 1
//
//  Teodor Ilie, 3564886
//  This program draws two houses - the first without anti-aliasing, and the second with anti-aliasing.
//  This is the main C++ file.

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

void initDisplay(int width, int height, std::string title) {
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    int windowHandle = glutCreateWindow("Program 1: Anti-aliasing");
    glutSetWindow(windowHandle);
    
    glClearColor (1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
}


void drawHouse1() {
    // draw rectangle with GL_POLYGON
    // set polygon mode to GL_LINE first
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f(-2.5f, 2.5f);
        glVertex2f(-2.0f, 0.5f);
        glVertex2f( 0.0f, 1.0f);
        glVertex2f(-0.5f, 3.0f);
    glEnd ();
    
    //draw triangle with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.75f, 3.50f, 0.0f);
        glVertex3f(-3.00f, 2.36f, 0.0f);
        glVertex3f( 0.00f, 3.14f, 0.0f);
    glEnd ();
}


void drawHouse2() {
    // enable anti-aliasing methods
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // draw rectangle with GL_POLYGON
    // set polygon mode to GL_LINE first
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, -1.5f);
        glVertex2f(-1.0f, -3.5f);
        glVertex2f( 1.0f, -3.0f);
        glVertex2f( 0.5f, -1.0f);
    glEnd ();
    
    //draw triangle with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.75f, -0.50f, 0.0f);
        glVertex3f(-2.00f, -1.64f, 0.0f);
        glVertex3f( 1.00f, -0.86f, 0.0f);
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
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

// main method
int main (int argc, char** argv) {
    
    glutInit (&argc, argv); // initialize glut
    initDisplay(400, 400, "Teodor Ilie, 3564886 - Program 1: Anti-aliasing"); //initialize display

    glutDisplayFunc(drawHouses);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
