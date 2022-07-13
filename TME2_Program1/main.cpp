/*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_2: 3DGraphics: Program 1
 
    @author: Teodor Ilie, 3564886
    @date: July 12, 2022
 
    This program draws, in 3D, the ground (green), the body (red), and the top (blue).
    It does this using a hierarchical structure of display lists.
    The ground is a simple rectangle, the body is a cube consisting of six squares,
    and the top is a pyramid consisting of four triangles.
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


typedef GLfloat list_3D [3];
// The local coordinates of the far-left-lower and near-right-upper corners of the body are
// {0,0,0}, and {1,1,1}, respectively.
list_3D square_coords [4] = {{0.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};

// The coordinates of the far-left and near-right corners of the pyramid are
// {-0.2, 1.0, -0.2} and {1.2, 1.0, 1.2}, respectively.
// The coordinate of the tip of the pyramid is {0.5, 1.5, 0.5}.

list_3D triangle_coords [3] = {{-0.2, 1.0, 1.2}, {1.2, 1.0, 1.2}, {0.5, 1.5, 0.5}};

// The far-left and near-right corners of the ground are at
// {-1.0, 0.0, -0.5} and {2.0, 0.0, 2.5}, respectively.
float bottom_coords [4][3] = {{-1.0, 0.0, 2.5}, {2.0, 0.0, 2.5}, {2.0, 0.0, -0.5}, {-1.0, 0.0, -0.5}};


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


// render method
void render() {
    // create variables that will be used to create the heirarchical structure
    // of the complex display list
    GLuint single_triangle, single_square, bottom_ground, top_pyramid, middle_body, house;
    // house has components bottom_ground, top_pyramid, middle_body
    // top_pyramid has components made from single_triangle
    // middle_body has components made from single_square
    
    // glGenLists generates an empty display list
    house = glGenLists(1);
    
    top_pyramid = glGenLists(1);
    middle_body = glGenLists(1);
    bottom_ground = glGenLists(1);
    
    single_triangle = glGenLists(1);
    single_square = glGenLists(1);
    
    // glPolygonMode sets mode to wire frame or solid
    // constant GL_LINE represents wire frame, which is what we need here
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // all display lists until 'house' are only compiled, not executed, using GL_COMPILE
    
    // display list for a square
    glNewList(single_square, GL_COMPILE);
        // set colour to red
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex3fv(square_coords[3]);
            glVertex3fv(square_coords[2]);
            glVertex3fv(square_coords[1]);
            glVertex3fv(square_coords[0]);
        glEnd();
    glEndList();
    
    // display list for a triangle
    glNewList(single_triangle, GL_COMPILE);
        //set colour to blue
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
            glVertex3fv(triangle_coords[2]);
            glVertex3fv(triangle_coords[1]);
            glVertex3fv(triangle_coords[0]);
        glEnd();
    glEndList();
    
    // display list for the bottom rectangle
    glNewList(bottom_ground, GL_COMPILE);
        // set colour to green
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex3fv(bottom_coords[3]);
            glVertex3fv(bottom_coords[2]);
            glVertex3fv(bottom_coords[1]);
            glVertex3fv(bottom_coords[0]);
        glEnd();
    glEndList();

    // display list for top_pyramid roof with 4 triangles
    glNewList(top_pyramid, GL_COMPILE);
    
        // forward facing triangle face
        glCallList(single_triangle);
    
        // rear facing triangle face
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(180, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_triangle);
        glPopMatrix();
    
        // left hand triangle face
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(-90, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_triangle);
        glPopMatrix();

        // right hand triangle face
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(90, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_triangle);
        glPopMatrix();
    glEndList();

    // display list for middle cube body with 6 squares
    glNewList(middle_body, GL_COMPILE);
    
        // forward facing square face
        glCallList(single_square);
        
        // rear facing square face
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(180, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_square);
        glPopMatrix();
    
        // right hand square
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(90, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_square);
        glPopMatrix();

        // left hand square
        glPushMatrix();
            glTranslatef(0.5, 0, 0.5);
            glRotatef(-90, 0, 1, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_square);
        glPopMatrix();
    
        // bottom square
        glPushMatrix();
            glTranslatef(0.5, 0.5, 0);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-0.5, 0, -0.5);
            glCallList(single_square);
        glPopMatrix();

        // top square
        glPushMatrix();
            glTranslatef(0.5, 0.5, 0);
            glRotatef(90, 1, 0, 0);
            glTranslatef(-0.5, 0, -1.5);
            glCallList(single_square);
        glPopMatrix();
    glEndList();
    
    // display list for the whole house
    // GL_COMPILE_AND_EXECUTE is used to execute all the display_lists after
    // compiling them using the hierarchical structure explained above
    glNewList(house, GL_COMPILE_AND_EXECUTE);
    
        // draw the bottom gorund
        glCallList(bottom_ground);
        // draw the middle body
        glCallList(middle_body);
        // draw the top pyramid
        glCallList(top_pyramid);
        
    
    glEndList();
}


// display method
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //set the viewing position
    gluLookAt(3, 3, 6.5, 0, 0, 0, 0, 1, 0);
    render();
    glutSwapBuffers();
}


// reshape method
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, 40);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main (int argc, char** argv) {
    // initialize glut
    glutInit (&argc, argv);
    
    // initialize display
    initDisplay(550, 550, "Teodor Ilie, 3564886 - Program 1: Object Modeling");
    
    // display
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
