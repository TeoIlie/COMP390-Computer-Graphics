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
// light 0 - back light
static const GLfloat light_pos_0_midday[] = { -1, 1, -0.3, 0 };
static const GLfloat light_pos_0_sunset[] = { -1, 0.1, -0.3, 0 };

static const GLfloat bright_back_light[] = { 0.2, 0.2, 0.2, 1.0 };
static const GLfloat dark_back_light[] = {1, 0.267, 0.222, 1.0};

// light 1 - sun light
// set in front of the drawn sun so that it both illuminates the sun
// itself, as well as shining on the objects of the scene from
// approximately the drawn sun's position
static const GLfloat light_pos_1_midday[] = { -40, 25, -12.5, 1.0 };
static const GLfloat light_pos_1_sunset[] = { -40, 0, -12.5, 1.0 }; 

static const GLfloat bright_sun_light[] = { 0.8, 0.467, 0.133, 1.0 };
static const GLfloat dark_sun_light[] = { 0.98, 0.372, 0.333, 1.0 };

// light 2 - TWEAK SOME MORE
static const GLfloat light_pos_2[] = { 3, 6.6, 5, 1.0 };
static const GLfloat spotlight_colour[] = { 1, 0.918, 0, 1.0 };
static const GLfloat spotlight_cutoff = 50.0;

// ambient
static const GLfloat bright_lmodel_ambient[] = { 0.7, 0.7, 0.71, 1.0 };
static const GLfloat dark_lmodel_ambient[] = { 0.5, 0.5, 0.51, 1.0 };

// fog colour variable
static const GLfloat bright_fog_colour[] = { 0.952, 0.812, 0.776, 1.0 };
static const GLfloat dark_fog_colour[] = { 1, 0.753, 0.796, 1.0 };
static const GLint fog_mode = GL_EXP2;


// surface properties
// wood 1 constants
static const GLfloat wood1_diffuse[] = {0.757, 0.604, 0.420, 1.0};
static const GLfloat wood1_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat wood1_shininess[] = {10};

// sail constants
static const GLfloat sail_diffuse[] = {0.391, 0.584, 0.929, 1.0};
static const GLfloat sail_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat sail_shininess[] = {50};

// wood 2 constants
static const GLfloat wood2_diffuse[] = {0.501, 0.274, 0.106, 1.0};
static const GLfloat wood2_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat wood2_shininess[] = {5};

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

// sunset constants
static const GLfloat sunset_diffuse[] = {1, 0.753, 0, 1.0};
static const GLfloat sunset_specular[] = {0.6, 0.6, 0.6, 1};
static const GLfloat sunset_shininess[] = {0};
static const GLfloat sunset_emissive[] = {1.0, 0.0, 0.0, 1.0};

// midday sun constants
static const GLfloat sun_diffuse[] = {1, 0.917, 0, 1.0};
static const GLfloat sun_specular[] = {0.5, 0.5, 0.5, 1};
static const GLfloat sun_shininess[] = {0};
static const GLfloat sun_emissive[] = {1.0, 0.0, 0.0, 1.0};

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

// wood 3 constants
static const GLfloat wood3_diffuse[] = {0.431, 0.204, 0.036, 1.0};
static const GLfloat wood3_specular[] = {0.580594, 0.223257, 0.0695701, 1.0};
static const GLfloat wood3_shininess[] = {5};

//lighthous beacon constants
static const GLfloat beacon_ambient[] = { 1, 0.918, 0, 1 };
static const GLfloat beacon_specular[] = { 1, 0, 0, 1 };
static const GLfloat beacon_shininess[] = { 100 };
static const GLfloat beacon_emissive[] = {1, 1, 1, 0};

// black rope constants
static const GLfloat black_diffuse[] = {0.361, 0.251, 0.2, 1};
static const GLfloat black_specular[] = {0.361, 0.251, 0.2, 1};
static const GLfloat black_shininess[] = {100};

static const GLfloat non_emissive[] = { 0.0, 0.0, 0.0, 1.0};

void set_material(int option);
#endif  // _LIGHTING_CONSTANTS_H_
