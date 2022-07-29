#ifndef _SCHEMATICS_H_
#define _SCHEMATICS_H_

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

class schematics {
    
public:
    schematics();
    void draw_reference();
    void draw_boat();
    void draw_deck(int pieces);
    void draw_cloud();
    void draw_ground();
    void draw_sun(int colour, bool draw_rays);
    void draw_lighthouse();
    
private:
    const int pi = 3.1415;
    const int slices = 20;
    GLuint cylinder;
    float radius, step_rad, step_degrees;
    float unit_circle[22][3];
    float unit_cylinder[42][3];
    void draw_cylinder();
    void draw_circle();
    void draw_deck_piece();
    
};

#endif  // _SCHEMATICS_H_
