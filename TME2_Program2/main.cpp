    /*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_2: 3DGraphics: Program 2

    @author: Teodor Ilie, 3564886
    @date: July 8, 2022
 
    Eight houses rendered with fill demonstrating the working of
    OpenGL's depth-buffer visibility-testing functionality.
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

// main_list will be populated later
GLuint main_list;

// save cube coordinates for reuse by single_square method
typedef GLint cube_list [3];

// The local coordinates of the far-left-lower and near-right-upper corners of the body are
// {0,0,0}, and {1,1,1}, respectively.
cube_list cube [8] = { {0,0,0}, {1,1,0}, {1,0,0}, {0,1,0}, {0,1,1}, {0,0,1}, {1,0,1}, {1,1,1} };

// save pyramid coordinates for reuse by single_triangle method
typedef GLfloat pyramid_list[3];

// The coordinates of the far-left and near-right corners of the pyramid are
// {-0.2, 1.0, -0.2} and {1.2, 1.0, 1.2}, respectively.
// The coordinate of the tip of the pyramid is {0.5, 1.5, 0.5}.
pyramid_list pyramid [5] = { {-0.2, 1.0, -0.2}, {1.2,1,-0.2}, {1.2, 1.0, 1.2}, {-0.2,1,1.2}, {0.5, 1.5, 0.5} };


// initialize the display
void initDisplay(int width, int height, std::string title) {
    
    // we must initialize with a request for a depth buffer and refresh buffer:
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    const char *display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);
    
    glClearColor (1.0, 1.0, 1.0, 0.0); // set background color to white.
}


// draw a triangle given 3 vertices
void single_triangle (GLint pos1, GLint pos2, GLint pos3) {
    //GL_POLYGON is required instead of GL_LINE_LOOP for drawing fill polygons
    glBegin (GL_POLYGON);
        glVertex3fv (pyramid[pos1]);
        glVertex3fv (pyramid[pos2]);
        glVertex3fv (pyramid[pos3]);
    glEnd();
}


// draw the entire blue top pyramid, made up of 4 triangles
void top_pyramid () {
    // set color to blue
    glColor3f(0.0, 0.0, 1.0);
    
    // individually draw each triangle
    single_triangle(4, 3, 0);
    single_triangle(4, 2, 3);
    single_triangle(4, 1, 2);
    single_triangle(4, 0, 1);
}


// draw a square given 4 vertices
void single_square (GLint pos1, GLint pos2, GLint pos3, GLint pos4) {
    //GL_POLYGON is required instead of GL_LINE_LOOP for drawing fill polygons
    glBegin (GL_POLYGON);
        glVertex3iv (cube[pos1]);
        glVertex3iv (cube[pos2]);
        glVertex3iv (cube[pos3]);
        glVertex3iv (cube[pos4]);
    glEnd();
}


// draw the entire middle red body, made up of 6 squares
void middle_body () {
    // set color to red
    glColor3f(1.0, 0.0, 0.0);
    
    // individually draw each square
    single_square (1, 3, 4, 7);
    single_square (0, 5, 6, 2);
    single_square (2, 1, 7, 6);
    single_square (4, 5, 6, 7);
    single_square (0, 2, 1, 3);
    single_square (0, 3, 4, 5);
}


// draw the bottom square; the ground
// The far-left and near-right corners of the ground are at
// {-1.0, 0.0, -0.5} and {2.0, 0.0, 2.5}, respectively.
void bottom_ground(){
    //set color to green
    glColor3f(0.0, 1.0, 0.0);
    //GL_POLYGON is required instead of GL_LINE_LOOP for drawing fill polygons
    glBegin (GL_POLYGON);
        glVertex3f (-1.0, 0.0, 2.5);
        glVertex3f (2.0, 0.0, 2.5);
        glVertex3f (2.0, 0.0, -0.5);
        glVertex3f (-1.0, 0.0, -0.5);
    glEnd();
}


// draw the grey ground
// The front-left and far-right coordinates of the ground (grey) are at
// {-8.0, -0.1, -8.0} and {8.0, -0.1, 8.0}, respectively.
void grey_ground(){
    //set colour to grey
    glColor3f(0.6, 0.6, 0.6);
    
    //GL_POLYGON is required instead of GL_LINE_LOOP for drawing fill polygons
    glBegin (GL_POLYGON);
        glVertex3f (-8.0, -0.1, 8.0);
        glVertex3f (8.0, -0.1, 8.0);
        glVertex3f (8.0,-0.1, -8.0);
        glVertex3f (-8.0, -0.1, -8.0);
    glEnd();
}

// initialize the display list
void initList() {
    //glGenLists generates an empty display list identified by main_list
    main_list = glGenLists(1);
    
    // create the main_list display list using glNewList
    // constant GL_COMPILE only compiles commands, without executing them
    glNewList(main_list, GL_COMPILE);
        //draw ground
        bottom_ground();
        //draw body
        middle_body();
        //draw pyramid
        top_pyramid();
    glEndList();
    
}


// render method displays 9 houses in total, using translations and rotations
// of the middle house (main_list). OpenGL depth testing is used for correct
// displaying on overlapping houses.
void render() {
    
    // enable depth-buffer visibility-detection routine
    // otherwise, houses are drawn overlapping in incorrect ways
    glEnable (GL_DEPTH_TEST);
    
    // glPolygonMode sets mode to wire frame or solid
    // constant GL_FILL represents a fill polygon, which is what we need here
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // draw the grey ground cover
    grey_ground();
    
    // middle
    glCallList(main_list);
    
    // right of middle
    glPushMatrix();
    glTranslatef(4, 0, 0);
    glCallList(main_list);
    glPopMatrix();
    
    // left of middle
    glPushMatrix();
    glTranslatef(-4, 0, 0);
    glCallList(main_list);
    glPopMatrix();
    
    // right of front
    glPushMatrix();
    glTranslatef(3, 0, 4);
    glScalef(2.0, 1.0, 1.0);
    glCallList(main_list);
    glPopMatrix();
    
    // left of front
    glPushMatrix();
    glTranslatef(-4, 0, 4);
    glScalef(1.8, 1.0, 1.0);
    glCallList(main_list);
    glPopMatrix();
   
    // right of back
    glPushMatrix();
    glTranslatef(5, 0, -5);
    glScalef(1.0, 2.0, 1.0);
    glCallList(main_list);
    glPopMatrix();
    
    // middle of back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1.5, 1.0, 1.0);
    glCallList(main_list);
    glPopMatrix();
    
    // left of back
    glPushMatrix();
    glTranslatef(-5, 0, -5);
    glRotatef(60, 0, 1 , 0); //rotation matrix
    glCallList(main_list);
    glPopMatrix();
}



// display method
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // set a farther viewing position than program 1 to encompass 8 houses
    gluLookAt(4, 5, 13, 0, 0, 0, 0, 1, 0);
    render();
    glutSwapBuffers();
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
int main (int argc, char** argv) {
    // initialize glut
    glutInit (&argc, argv);
    
    // initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 2: 3D Transformation and Projection");
    
    // initialize display list
    initList();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
