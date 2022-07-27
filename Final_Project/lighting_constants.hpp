#ifndef _LIGHTING_CONSTANTS_H_
#define _LIGHTING_CONSTANTS_H_

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


// lighting variable
// light 0
static const GLfloat light_pos_0[] = { 0, 0, -1, 0.0 };
static const GLfloat sun_light[] = { 1.0, 1.0, 1.0, 1.0 };

// light 1
static const GLfloat light_pos_1[] = { 5.0, 12.5, -7.5, 1.0 };
static const GLfloat warm_light[] = { 0.8, 0.467, 0.133, 1.0 };

// ambient
static const GLfloat lmodel_ambient[] = { 0.7, 0.7, 0.71, 1.0 };

// fog colour variable
static const GLfloat fog_colour[] = { 0.952, 0.812, 0.776, 1.0 };
static const GLint fog_mode = GL_EXP2;


// surface properties
// wood 1 constants
static const GLfloat wood1_diffuse[] = {0.757, 0.604, 0.420, 1.0};
static const GLfloat wood1_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat wood1_shininess[] = {50};

// sail constants
static const GLfloat sail_diffuse[] = {0.391, 0.584, 0.929, 1.0};
static const GLfloat sail_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat sail_shininess[] = {50};

// wood 2 constants
static const GLfloat wood2_diffuse[] = {0.501, 0.274, 0.106, 1.0};
static const GLfloat wood2_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat wood2_shininess[] = {20};

// cloud constants
static const GLfloat cloud_diffuse[] = {0.976, 0.965, 0.933, 1.0};
static const GLfloat cloud_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
static const GLfloat cloud_shininess[] = {20};

// sand constants
static const GLfloat sand_diffuse[] = {0.811, 0.698, 0.452, 1.0};
static const GLfloat sand_specular[] = { 0.25, 0.85, 0.25 };
static const GLfloat sand_shininess[] = {20};

// water constants
static const GLfloat water_diffuse[] = {0.529, 0.808, 0.922, 1.0};
static const GLfloat water_specular[] = {0.0, 1.0, 1.0, 1.0};
static const GLfloat water_shininess[] = {70};

// sun constants
static const GLfloat sun_diffuse[] = {1, 0.753, 0, 1.0};
static const GLfloat sun_specular[] = {0.1, 0.1, 0.1};
static const GLfloat sun_shininess[] = {0};
static const GLfloat sun_emissive[] = {1, 0.753, 0};

// ray constants
static const GLfloat ray_diffuse[] = {1, 0.917, 0, 1.0};
static const GLfloat ray_specular[] = {0, 0, 0};
static const GLfloat ray_shininess[] = {0};
static const GLfloat ray_emissive[] = {1, 0.917, 0,};

// silver metal constants
static const GLfloat metal_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
static const GLfloat metal_diffuse[] = { 0.70754, 0.70754, 0.70754, 1.0 };
static const GLfloat metal_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
static const GLfloat metal_shininess[] = { 51.2 };

// red metal constants
static const GLfloat red_ambient[] = {0.647, 0.165, 0.165, 1.0};
static const GLfloat red_diffuse[] = {0.649, 0.167, 0.167, 1.0};
static const GLfloat red_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
static const GLfloat red_shininess[] = { 51.2 };

static const GLfloat non_emissive[] = { 0.0, 0.0, 0.0, 1.0};

void set_material(int option);
#endif  // _LIGHTING_CONSTANTS_H_
