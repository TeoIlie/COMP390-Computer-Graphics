/*  Athabasca University
    Comp390 - Introduction to Computer Graphics

    Final Project

    @author: Teodor Ilie, 3564886
    @date: July 29, 2022
 
    Option 1: Scene of a port on a beach. Includes
    - a textured background
    - Five 3D composite objects:
        - sun with rays of light, made of 1 sphere and 20 cylindrical rays
        - clouds made of 5 translated, scaled spheres 
        - wooden deck made of 8 pieces, where each piece is made of 4
          cylinders and a polygon.
        - sailboat made up of 7 polygons for the hull, 2 polygons for the seats,
          and 2 cylinders and 1 triangle for the sail
        - lighthouse made up of 6 cylinders, 1 torus, and 1 cone
    - Two light sources:
        - GL_LIGHT0 is a distant light source which simulates sunlight
          coming from the rear bottom of the scene.
        - GL_LIGHT1 is a point light source which comes from the rear
          top right of the scene and adds a warm tint to the beach scene.
    - A fog effect with a pinkish beige colours that is concentrated at
      the rear of the scene by setting the OpenGL fog mode to GL_EXP2.
    - A ground made of sand and water
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


// include the schematics for drawing scene elements, and the lighting
// properties for materials and lights
#include "schematics.hpp"
#include "lighting_constants.hpp"
#include "vector3.hpp"

// set display window aspect ratio
int window_height = 500;
int window_width = 925;

// use an schematics instance to draw schematics
schematics ob;

// set viewing position
//vector3 viewer(20, 20, -20);
vector3 viewer(21, 6, -8);


// initialize the display
void initDisplay(std::string title) {
    
    // we must initialize with a request for a depth buffer and refresh buffer
    // adding a multisampling buffer makes polygons anti-aliased, and the state
    // of GL_LINE_SMOOTH and GL_POLYGON_SMOOTH are ignored, so we need not set them
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);

    // set window title
    const char *display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);
    
    // set background color to white.
    glClearColor (1.0, 1.0, 1.0, 0.0);
    
    // enable depth-buffer visibility-detection routine
    glEnable (GL_DEPTH_TEST);
    
    // glPolygonMode sets mode to wire frame or solid
    // constant GL_FILL represents a fill polygon, which is what we need here
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // enable lighting
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    // set ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    // set light 0
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos_0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light);
    
    // set light 0
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos_1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, warm_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, warm_light);
    
    // create fog atmospheric effect
    glFogi(GL_FOG_MODE, fog_mode);
    glFogfv(GL_FOG_COLOR, fog_colour);
    glFogf(GL_FOG_DENSITY, 0.03);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, 1.0);
    glFogf(GL_FOG_END, 5.0);
    glEnable(GL_FOG);
}


// method for placing coordinate reference frame
// used exclusively for testing
void test(){
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        ob.draw_reference();
    glPopMatrix();
}


// render method
void render() {
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);

    // test();
    
    // draw the boat
    glPushMatrix();
        glTranslatef(13, 0.2,0);
        glRotatef(170.0, 0.0, 1.0, 0.0);
        glRotatef(1.0, 0.0, 0.0, 1.0);
        ob.draw_boat();
    glPopMatrix();
    
    // draw another boat
    glPushMatrix();
        glTranslatef(1, 0.2, 0);
        glScalef(1, 1, 1);
        glRotatef(130.0, 0.0, 1.0, 0.0);
        glRotatef(-5.0, 0.0, 0.0, 1.0);
        ob.draw_boat();
    glPopMatrix();
    
    // draw the ground
    glPushMatrix();
        // the large scale creates the impression of a horizon
        glScalef(15, 15, 15);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        ob.draw_ground();
    glPopMatrix();
    
    // draw the deck
    glPushMatrix();
        glTranslatef(6, 0.8,3);
        glScalef(0.7, 0.9, 0.7);
        glRotatef(80.0, 0.0, 1.0, 0.0);
        ob.draw_deck(8);
    glPopMatrix();
    
    // draw two clouds
    glPushMatrix();
        glTranslatef(-5, 10, 5);
        glScalef(1, 1, 1);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        ob.draw_cloud();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(3, 11, 12);
        glScalef(1, 1, 1);
        glRotatef(270.0, 0.0, 1.0, 0.0);
        glRotatef(-20.0, 1.0, 0.0, 0.0);
        ob.draw_cloud();
    glPopMatrix();
    
    // draw the sun
    glPushMatrix();
        glTranslatef(-15, 14, -15);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glRotatef(-25.0, 0.0, 1.0, 0.0);
        glScalef(0.5, 0.5, 0.5);
        ob.draw_sun();
    glPopMatrix();
    
    // draw the lignthouse
    glPushMatrix();
        glTranslatef(-12, 0, -3);
        glScalef(0.6,0.6,0.6);
        ob.draw_lighthouse();
    glPopMatrix();
}


// display method
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // set viewing position
    gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    render();
    glutSwapBuffers();
}


// reshape method
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)window_width/window_height, 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main (int argc, char** argv) {
    // initialize glut
    glutInit (&argc, argv);
    
    // initialize display
    initDisplay("Final Project");
    
    // display
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop ();
}
