/*  Athabasca University
    Comp390 - Introduction to Computer Graphics

    Final Project

    @author: Teodor Ilie, 3564886
    @date: July 29, 2022
 
    All functions for drawing scene objects are defined here.
    All methods are public except for draw_circle, draw_cylinder
    and draw_deck_piece which are used by other public methods
    of the class.
*/

#include "schematics.hpp"
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

#include "lighting_constants.hpp"
#include "vector3.hpp"
#include <math.h>

GLfloat bottom_boat_coords[6][3] = {{-2, 0,  2}, { 0, 0,  4}, { 2, 0,  2}, { 2, 0, -2}, { 0, 0, -4}, {-2, 0, -2}};
GLfloat top_boat_coords[6][3] = {{-2.5, 1,  2.5}, { 0, 2,  5}, { 2.5, 1,  2.5}, { 2.5, 1, -2.5}, { 0, 2, -5}, {-2.5, 1, -2.5}};
GLfloat boat_seat_coords[4][3] = {{-2.5, 1, -1.5}, {-2.5, 1,  1.5}, { 2.5, 1,  1.5}, { 2.5, 1, -1.5}};
GLfloat ground[4][3] = {{-8,0,-6}, {-8,0,6}, {8,0,6}, {8,0,-6}};


schematics::schematics() {
    // set initial radius and angle
    radius = 1.0;
    step_rad = 6.2832 / slices;
    step_degrees = 360.0 / slices;
    
    // initial coordinates of a unit circle
    unit_circle [0][0] = 0.0;
    unit_circle [0][1] = 0.0;
    unit_circle [0][2] = 0.0;
    
    // instantiate points for unit circles and unit cylinders
    for (int i = 0; i <= slices; ++i) {
        unit_circle[i+1][0] = radius * cosf(step_rad * i);
        unit_circle[i+1][1] = 0.0;
        unit_circle[i+1][2] = radius * sinf(step_rad * i);
        
        unit_cylinder[2*i][0] = unit_circle[i+1][0];
        unit_cylinder[2*i][1] = unit_circle[i+1][1];
        unit_cylinder[2*i][2] = unit_circle[i+1][2];
        
        unit_cylinder[2*i+1][0] = unit_circle[i+1][0];
        unit_cylinder[2*i+1][1] = unit_circle[i+1][1] + radius;
        unit_cylinder[2*i+1][2] = unit_circle[i+1][2];
    }
}


// draw a circle
void schematics::draw_circle() {
    glBegin(GL_TRIANGLE_FAN);
        for(int index = 0; index < slices + 2; index++) {
            glVertex3fv(unit_circle[index]);
        }
    glEnd();
}


// draw a unit cylinder
void schematics::draw_cylinder() {
    
    draw_circle();
    glPushMatrix();
        glTranslatef(0.0, radius, 0.0);
        draw_circle();
    glPopMatrix();
    
    glBegin(GL_QUADS);
        for(int i = 0; i < slices; ++i) {
            glVertex3fv(unit_cylinder[2*i+2]);
            glVertex3fv(unit_cylinder[2*i+3]);
            glVertex3fv(unit_cylinder[2*i+1]);
            glVertex3fv(unit_cylinder[2*i]);
        }
    glEnd();
}


// draw a peice of the deck which is then repeated in draw_deck()
void schematics::draw_deck_piece(){
    set_material(2);
    
    // draw base
    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glVertex3f(-1.4, 0, -2);
            glVertex3f(-1.4, 0, 2);
            glVertex3f(1.4, 0, 2);
            glVertex3f(1.4, 0, -2);
        glEnd();
    glPopMatrix();
    
    // draw 4 wooden pillars
    glPushMatrix();
        glTranslatef(-1.4, -2.5, -2);
        glScalef(0.2,3,0.2);
        draw_cylinder();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-1.4, -2.5, 2);
        glScalef(0.2,3,0.2);
        draw_cylinder();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.4, -2.5, 2);
        glScalef(0.2,3,0.2);
        draw_cylinder();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.4, -2.5, -2);
        glScalef(0.2,3,0.2);
        draw_cylinder();
    glPopMatrix();
}


// reference frame used for testing purposes
void schematics::draw_reference(){
    // white circle at center
    set_material(3);
    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(2.0, 2.0, 2.0);
        glutSolidSphere(1.0, 64, 10);
    glPopMatrix();
    
    // red square in x-direction
    set_material(9);
    glPushMatrix();
        glTranslatef(10,0,0);
        glScalef(2.0, 2.0, 2.0);
        glutSolidSphere(1.0, 64, 10);
    glPopMatrix();
    
    // yellow square in z-direction
    set_material(6);
    glPushMatrix();
        glTranslatef(0,0,10);
        glScalef(2.0, 2.0, 2.0);
        glutSolidSphere(1.0, 64, 10);
    glPopMatrix();
    
    // brown square in y-direction
    set_material(0);
    glPushMatrix();
        glTranslatef(0,10,0);
        glScalef(2.0, 2.0, 2.0);
        glutSolidSphere(1.0, 64, 10);
    glPopMatrix();
}


// draw a sailboat
void schematics::draw_boat(){
    
    // set material properties
    set_material(0);
    
    // draw bottom of boat
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            vector3 v1 = vector3(
                 bottom_boat_coords[1][0] - bottom_boat_coords[0][0],
                 bottom_boat_coords[1][1] - bottom_boat_coords[0][1],
                 bottom_boat_coords[1][2] - bottom_boat_coords[0][2]);
            vector3 v2 = vector3(
                 bottom_boat_coords[2][0] - bottom_boat_coords[1][0],
                 bottom_boat_coords[2][1] - bottom_boat_coords[1][1],
                 bottom_boat_coords[2][2] - bottom_boat_coords[1][2]);
            vector3 normal = v1.cross(v2).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[0]);
            glVertex3fv(bottom_boat_coords[1]);
            glVertex3fv(bottom_boat_coords[2]);
            glVertex3fv(bottom_boat_coords[3]);
            glVertex3fv(bottom_boat_coords[4]);
            glVertex3fv(bottom_boat_coords[5]);
        glEnd();
    glPopMatrix();
    
    // draw 6 sides of boat, and specify normals
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[1][0] - bottom_boat_coords[0][0],
                 bottom_boat_coords[1][1] - bottom_boat_coords[0][1],
                 bottom_boat_coords[1][2] - bottom_boat_coords[0][2]);
            v2 = vector3(
                 top_boat_coords[1][0] - bottom_boat_coords[1][0],
                 top_boat_coords[1][1] - bottom_boat_coords[1][1],
                 top_boat_coords[1][2] - bottom_boat_coords[1][2]);
            normal = v1.cross(v2).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[0]);
            glVertex3fv(bottom_boat_coords[1]);
            glVertex3fv(top_boat_coords[1]);
            glVertex3fv(top_boat_coords[0]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[1][0] - bottom_boat_coords[2][0],
                 bottom_boat_coords[1][1] - bottom_boat_coords[2][1],
                 bottom_boat_coords[1][2] - bottom_boat_coords[2][2]);
            v2 = vector3(
                 top_boat_coords[2][0] - bottom_boat_coords[2][0],
                 top_boat_coords[2][1] - bottom_boat_coords[2][1],
                 top_boat_coords[2][2] - bottom_boat_coords[2][2]);
            normal = v2.cross(v1).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[1]);
            glVertex3fv(bottom_boat_coords[2]);
            glVertex3fv(top_boat_coords[2]);
            glVertex3fv(top_boat_coords[1]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[3][0] - bottom_boat_coords[2][0],
                 bottom_boat_coords[3][1] - bottom_boat_coords[2][1],
                 bottom_boat_coords[3][2] - bottom_boat_coords[2][2]);
            v2 = vector3(
                 top_boat_coords[2][0] - bottom_boat_coords[2][0],
                 top_boat_coords[2][1] - bottom_boat_coords[2][1],
                 top_boat_coords[2][2] - bottom_boat_coords[2][2]);
            normal = v1.cross(v2).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[2]);
            glVertex3fv(bottom_boat_coords[3]);
            glVertex3fv(top_boat_coords[3]);
            glVertex3fv(top_boat_coords[2]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[3][0] - bottom_boat_coords[4][0],
                 bottom_boat_coords[3][1] - bottom_boat_coords[4][1],
                 bottom_boat_coords[3][2] - bottom_boat_coords[4][2]);
            v2 = vector3(
                 top_boat_coords[4][0] - bottom_boat_coords[3][0],
                 top_boat_coords[4][1] - bottom_boat_coords[3][1],
                 top_boat_coords[4][2] - bottom_boat_coords[3][2]);
            normal = v2.cross(v1).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[3]);
            glVertex3fv(bottom_boat_coords[4]);
            glVertex3fv(top_boat_coords[4]);
            glVertex3fv(top_boat_coords[3]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[4][0] - bottom_boat_coords[5][0],
                 bottom_boat_coords[4][1] - bottom_boat_coords[5][1],
                 bottom_boat_coords[4][2] - bottom_boat_coords[5][2]);
            v2 = vector3(
                 top_boat_coords[5][0] - bottom_boat_coords[5][0],
                 top_boat_coords[5][1] - bottom_boat_coords[5][1],
                 top_boat_coords[5][2] - bottom_boat_coords[5][2]);
            normal = v2.cross(v1).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[4]);
            glVertex3fv(bottom_boat_coords[5]);
            glVertex3fv(top_boat_coords[5]);
            glVertex3fv(top_boat_coords[4]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin (GL_POLYGON);
            // calculate v2, v1
            v1 = vector3(
                 bottom_boat_coords[5][0] - bottom_boat_coords[0][0],
                 bottom_boat_coords[5][1] - bottom_boat_coords[0][1],
                 bottom_boat_coords[5][2] - bottom_boat_coords[0][2]);
            v2 = vector3(
                 top_boat_coords[0][0] - bottom_boat_coords[0][0],
                 top_boat_coords[0][1] - bottom_boat_coords[0][1],
                 top_boat_coords[0][2] - bottom_boat_coords[0][2]);
            normal = v2.cross(v1).normalize();
            // set normal using vector cross product
            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3fv(bottom_boat_coords[5]);
            glVertex3fv(bottom_boat_coords[0]);
            glVertex3fv(top_boat_coords[0]);
            glVertex3fv(top_boat_coords[5]);
        glEnd();
    glPopMatrix();
    
    // draw boat seats
    glPushMatrix();
        glBegin(GL_POLYGON);
            // set custom normal to look different than boat bottom
            glNormal3f(0,0.8,0);
            glVertex3fv(top_boat_coords[5]);
            glVertex3fv(boat_seat_coords[0]);
            glVertex3fv(boat_seat_coords[3]);
            glVertex3fv(top_boat_coords[3]);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glBegin(GL_POLYGON);
            // set custom normal to look different than boat bottom
            glNormal3f(0,0.8,0);
            glVertex3fv(top_boat_coords[0]);
            glVertex3fv(top_boat_coords[2]);
            glVertex3fv(boat_seat_coords[2]);
            glVertex3fv(boat_seat_coords[1]);
        glEnd();
    glPopMatrix();
    
    // draw mast
    glPushMatrix();
        glScalef(0.2, 6, 0.2);
        draw_cylinder();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0,3,0);
        glRotated(90, 1, 0, 0);
        glRotatef(150, 0, 0, 1);
        glScalef(0.2, 3, 0.2);
        draw_cylinder();
    glPopMatrix();
    
    set_material(1);
    
    // draw sail
    glPushMatrix();
        glRotatef(-150, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 6, 0);
            glVertex3f(0, 3, 3);
            glVertex3f(0, 3, 0);
        glEnd();
    glPopMatrix();
}


// draw a deck made up of a certain number of pieces given as input
void schematics::draw_deck(int pieces){
    // draw deck piece by piece
    for (int i = 0; i < pieces; i++) {
        glPushMatrix();
            glTranslatef(i * 2.8,0,0);
            draw_deck_piece();
        glPopMatrix();
    }
}


// draw a cloud made up of stretched spheres
void schematics::draw_cloud(){
    // set material and draw spheres to make clouds look puffy
    set_material(3);
    glPushMatrix();
        glScalef(0.5,0.3,0.6);
        glutSolidSphere(5,20,20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0.5, 0.5);
        glScalef(0.55,0.4,0.65);
        glutSolidSphere(4,20,20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1.5, -0.5, -1);
        glScalef(0.55,0.4,0.65);
        glutSolidSphere(4,20,20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(2, 0.5, -1.5);
        glScalef(0.55,0.4,0.65);
        glutSolidSphere(3,20,20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(1, 0.8, -2.5);
        glScalef(0.85,0.4,1);
        glutSolidSphere(3,20,20);
    glPopMatrix();
}


// draw the ground with sand and water
void schematics::draw_ground(){
    // draw water
    set_material(5);
    glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3fv(ground[0]);
            glVertex3fv(ground[1]);
            glVertex3fv(ground[2]);
            glVertex3fv(ground[3]);
        glEnd();
    glPopMatrix();
    
    //overlay sand
    set_material(4);
    glPushMatrix();
        glTranslatef(0, 0.01, 0);
        glBegin(GL_POLYGON);
            glVertex3fv(ground[0]);
            glVertex3fv(ground[1]);
            glVertex3f(-5,0,6);
            glVertex3f(-3,0,5);
            glVertex3f(-1,0,3);
            glVertex3f(-.5,0,1);
            glVertex3f(2,0,-4);
            glVertex3f(2.5,0,-6);
        glEnd();
    glPopMatrix();
}


// draw the sun with spherical body and cylindrical rays
void schematics::draw_sun(){
    
    //disable fog so that sun appear bright in the sky
    glDisable(GL_FOG);
    set_material(6);
    
    // draw spherical body
    glPushMatrix();
        glutSolidSphere(4, 20, 20);
    glPopMatrix();
    
    // draw rays
    set_material(7);
    for(int i = 0; i < 20; ++i){
        glPushMatrix();
            glRotatef(18 * i, 0, 0, 1);
            glScalef(0.2, 8, 0.2);
            draw_cylinder();
        glPopMatrix();
    }
    glEnable(GL_FOG);
}


// draw the lighthouse
void schematics::draw_lighthouse(){

    // draw red and grey concentric cylinders for tower
    set_material(9);
    glPushMatrix();
        glScalef(3,2,3);
        draw_cylinder();
    glPopMatrix();

    set_material(8);
    glPushMatrix();
        glTranslatef(0,2,0);
        glScalef(2.8,2,2.8);
        draw_cylinder();
    glPopMatrix();
    
    set_material(9);
    glPushMatrix();
        glTranslatef(0,4,0);
        glScalef(2.6,2,2.6);
        draw_cylinder();
    glPopMatrix();

    set_material(8);
    glPushMatrix();
        glTranslatef(0,6,0);
        glScalef(2.4,2,2.4);
        draw_cylinder();
    glPopMatrix();
    
    set_material(9);
    glPushMatrix();
        glTranslatef(0,8,0);
        glScalef(2.2,2,2.2);
        draw_cylinder();
    glPopMatrix();
    
    // draw yellow center as a torus to appear rounded
    set_material(7);
    glPushMatrix();
        glTranslatef(0,11,0);
        glScalef(1,1.5,1);
        glRotatef(90, 1, 0, 0);
        glutSolidTorus(1, 1, 20, 20);
    glPopMatrix();
    
    // draw roof as a cone and cylinder
    set_material(9);
    glPushMatrix();
        glTranslatef(0, 12, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 2.2, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0,12,0);
        glScalef(0.5, 2.5, 0.5);
        draw_cylinder();
    glPopMatrix();
}

