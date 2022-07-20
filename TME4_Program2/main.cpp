/*  Athabasca University
    Comp390 - Introduction to Computer Graphics
    
    TME_4: Ray Tracing: Program 2
    @author: Teodor Ilie, 3564886
    @date: July 22, 2022
 
    Implementation of a recursive ray-tracing routine that
    is used to produce a reflective effect and a shadow.
    Makes use of vector3.cpp, vector.h, plane.cpp, plane.h
    and the reflection program from Objective 11.2.1.
*/

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>

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

#include "plane.h"

using namespace std;

// viewer position changed for better view
vector3 viewer(-60.0, 80.0, 120.0);

// floor
vector3 floorNormal(0.0, 1.0, 0.0);
plane   floorDef(0.0, 4.0, 0.0, 0.0);
vector3 floorLimit1(-75.0, 0, -75.0);
vector3 floorLimit2(-75.0, 0, 75.0);
vector3 floorLimit3(75.0, 0, 75.0);
vector3 floorLimit4(75.0, 0, -75.0);
    
// wall
vector3 wallNormal(0.0, 0.0, 1.0);
plane   wall(0.0, 0.0, 4.0, 0.0);
vector3 wallLimit1(-25.0, 0.0, 0.0);
vector3 wallLimit2(-25.0, 50.0, 0.0);
vector3 wallLimit3(25.0, 50.0, 0.0);
vector3 wallLimit4(25.0, 0.0, 0.0);

// colors
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);

// lighting position
vector3 lightPosition(80, 80, 100.0);

// lighting elements
float ambient_coef = 0.3;
float diffuse_coef = 0.7;
float reflect_coef = 0.4;
float local_coef   = 0.6;


// initialize the display
void initDisplay(int width, int height, std::string title) {
    
    // we initialize with a request for a depth buffer and refresh buffer
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    const char *display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);
    
    // set background colour
    glClearColor(0.5, 0.7, 0.5, 0.0);
}


// calculate local color
// local color is intensity * base color
vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {
    // calculate unit vector
    vector3 origin = lightPosition.subtract(intersect);
    vector3 unitVec = origin.normalize();

    // calculate dot product
    float dotProd = unitVec.dot(normal);

    // calculate intensity
    float ambientContr = ambient_coef;
    float diffuseContr = diffuse_coef * dotProd;
    float intensity = ambientContr + diffuseContr;

    if (intensity > 1.0) intensity = 1.0;

    float r = intensity * baseColor.x;
    float g = intensity * baseColor.y;
    float b = intensity * baseColor.z;

    return vector3(r,g,b);
}


// ray tracing algorithm based on template from objective 10.2.3, with shadows omitted
vector3 recursiveRayTrace(vector3 incident_1, vector3 incident_2, int recursion_depth) {
    // find intersection of the ray with the wall and the floor
    vector3 floor_intersect = floorDef.intersect(incident_1, incident_2);
    vector3 wall_intersect = wall.intersect(incident_1, incident_2);
    


    // if the ray hits an opaque wall stop recursion, based on inclusion test
    if ((wall_intersect.x >= -25.0) && (wall_intersect.y >= 0.0) && (wall_intersect.x <= 25.0)
        && (wall_intersect.y <= 50.0)){
            return localColor(wall_intersect, lightRed, wallNormal);
    }
    // if the object at intersection point is reflective, based on inclusion test
    else if ((floor_intersect.x >= -75.0) && (floor_intersect.z >= -75.0) && (floor_intersect.x <= 75.0)
        && (floor_intersect.z <= 75.0)){
        
        vector3 shadow_intersect = wall.intersect(incident_1, lightPosition);

        if ((shadow_intersect.y >= 0.0) && (shadow_intersect.y <= 50.0) 
            && (shadow_intersect.x >= -25.0) && (shadow_intersect.x <= 25.0)) {
                vector3 shadow = grey.scalar(ambient_coef);
                return shadow;
        }
        else{
                // find the reflective ray
                vector3 reflective_ray = incident_2.subtract(incident_1);
                reflective_ray = (reflective_ray.reflect(floorNormal)).add(incident_1);
                
                // use recursion to calculate reflective colour and compute overall colour per light source
                // Color per light source = (Local color * local color contribution percentage) +
                // (Reflective color * reflective color contribution percentage)
                return ((localColor(incident_1, grey, floorNormal)).scalar(local_coef)).add(
                            (recursiveRayTrace(reflective_ray, incident_1, ++recursion_depth).scalar(reflect_coef)));
        }
    }
    // if the ray hits nothing, return grey colour
    else {
        return localColor(floor_intersect, grey, floorNormal);
    }
}


// render method
void render() {
    // render the floor
    for (int i=-75; i < 75; i++) {
        for (int j=-75; j < 75; j++) {
            vector3 intersect = vector3(i,0,j);
            
            // call the recursive ray trace method to determine colour
            vector3 color = recursiveRayTrace(intersect, viewer, 0);
            
            glColor3f(color.x, color.y, color.z);

            // use the small rectangles method
            glBegin(GL_POLYGON);
                glVertex3i(i, 0, j);
                glVertex3i(i+1, 0, j);
                glVertex3i(i+1, 0, j+1);
                glVertex3i(i, 0, j+1);
            glEnd();
        }
    }
    
    // render the wall - non-reflective surface
    for (int m=-25; m<25; m++) {
        for(int n=0; n<50; n++) {
            // use recursive ray trace method to find colour
            vector3 intersect_vector(m, n, 0.0);
            vector3 color = recursiveRayTrace(intersect_vector, viewer, 0);

            glColor3f(color.x, color.y, color.z);
            glRecti(m, n, m+1, n+1);
        }
    }
}


// display registry
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    render();

    glutSwapBuffers();
}


// reshape registry
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // change frustrum so the whole floor renders
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 300);
    glMatrixMode(GL_MODELVIEW);
}


// main program
int main(int argc, char **argv) {
    // initialize glut
    glutInit( &argc, argv );
    
    // initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 1: Recursive reflection");

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );

    glutMainLoop();
}
