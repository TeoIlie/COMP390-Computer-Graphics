/*  Athabasca University
Comp390 - Introduction to Computer Graphics
 
TME_3: Lighting and Surface Textures: Program 2
 
@author: Teodor Ilie, 3564886
@date: July 15, 2022
 
This program adds specular contribution to the existing
ambient and diffuse contributions already calculated in
code from Unit 8, Section 3, Objective 8.3.1. This makes the
bright patch on the red square appear more intense around the
centre and less spread out.
*/


#include <stdlib.h>
#include <fstream>
#include <iostream>
// required for power function
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
#include "vector3.h"


using namespace std;

// set distance of viewer >100 in z-direction
vector3 viewer(0.0, 0.0, 120.0);
// square
vector3 wallNormal(0.0, 0.0, 1.0);
// colors
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);
// lighting position
vector3 lightPosition(10, 10, 10);
// lighting elements
float ambient_coef = 0.3;
float diffuse_coef = 0.7;
// additional values for specular coeffient and exponent
float specular_exp = 25.0;
float specular_coef = 0.7;


// initialize
void initialize() {
    // set background color
    glClearColor(0.5, 0.7, 0.5, 0.0);
}


// calculate local color, using ambient, diffuse, and specular contributions
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
    
    // specular contribution calculations
	// calculate reflection vector
	vector3 reflectVector = (normal.scalar((normal.scalar(2.0)).dot(unitVec))).subtract(unitVec);
	// calculate dot product of reflection-vector and view-vector
	float specDotProd = reflectVector.dot(viewer.normalize());
	// calculate specular intensity contribution using coefficient, exponent, and dot product
	float specularContr = specular_coef * powf(specDotProd, specular_exp);
    
	// add specular contribution to total intensity
	float intensity = ambientContr + diffuseContr + specularContr;
    
    if (intensity > 1.0) intensity = 1.0;
    float r = intensity * baseColor.x;
    float g = intensity * baseColor.y;
    float b = intensity * baseColor.z;
    return vector3(r,g,b);
}


// render
void render() {
    // render the square
    for (int m=-25; m<25; m++) {
        for(int n=-25; n<25; n++) {
            vector3 color = localColor(vector3(m,n,0), lightRed, wallNormal);
            glColor3f(color.x, color.y, color.z);
            glRecti(m, n, m+1, n+1);
        }
    }
}


// display registry
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //  gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    render();
    glutSwapBuffers();
}


// reshape registry
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 250.0);
    glMatrixMode(GL_MODELVIEW);
}


// main program
int main(int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    int windowHandle = glutCreateWindow("Teodor Ilie, 3564886 - Program 2: Specular contribution");
    glutSetWindow(windowHandle);
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    initialize();
    glutMainLoop();
}
