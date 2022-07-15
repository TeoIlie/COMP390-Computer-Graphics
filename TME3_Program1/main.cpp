/*  Athabasca University
Comp390 - Introduction to Computer Graphics

TME_3: Lighting and Surface Textures: Program 1

@author: Teodor Ilie, 3564886
@date: July 15, 2022

A program to light a sphere using OpenGL’s lighting features. There are 3
light sources, with colour options red, blue, green, and white, 3 surface
materials, and options for light types. All options are available by
right-clicking to bring up the submenus.
 
Note: by default the sphere will appear black. A light source, material, and
lighting type must be selected for a lit sphere to be rendered.
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


// colour value variables
GLfloat light1_red = 0.0, light1_green= 0.0, light1_blue= 0.0;
GLfloat light2_red = 0.0, light2_green= 0.0, light2_blue= 0.0;
GLfloat light3_red = 0.0, light3_green= 0.0, light3_blue= 0.0;
GLfloat light_properties[3];
GLfloat diffuse[4], shininess[1], specular[4];

// light positions and colours
static const GLfloat light1_colour[] = { light1_red, light1_green, light1_blue, 1.0 };
static const GLfloat light2_colour[] = { light2_red, light2_green, light2_blue, 1.0 };
static const GLfloat light3_colour[] = { light3_red, light3_green, light3_blue, 1.0 };

static const GLfloat light1_pos[] = { -10.0, 10.0, 10.0, 0.0 }; // top left corner
static const GLfloat light2_pos[] = { 10.0, 10.0, 10.0, 0.0 }; // top right corner
static const GLfloat light3_pos[] = { 0, 0, 7, 0 }; // directly behind viewer
static const GLfloat ambient_light[] = { 0.3, 0.3, 0.3, 1.0 };


// default parameters for material properties
// gold
static const GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };
static const GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };
static const GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };
static const GLfloat gold_shininess[] = { 51.2 };

// silver
static const GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
static const GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
static const GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
static const GLfloat silver_shininess[] = { 51.2 };

// copper
static const GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };
static const GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };
static const GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };
static const GLfloat copper_shininess[] = { 51.2 };


// initialize the display
void initDisplay(int width, int height, std::string title) {
    
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    const char *display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);
    
    // set background colour
    glClearColor(0.5, 0.7, 0.5, 0.0);
    
    // enable colour blending routine
    glEnable (GL_BLEND);
    
    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // enable lighting routine and set ambient light
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
}


// main menu is activated by right mouse click
void main_menu(GLint render_option){
    //to renew current display
    glutPostRedisplay();
}


// sub menu to set the colour of light 1
void l1_sub_menu(GLint colour_option){
    switch (colour_option) {
        // off
        case 1:
            light1_red = 0;
            light1_green = 0;
            light1_blue = 0;
        break;
        // white
        case 2:
            light1_red = 1;
            light1_green = 1;
            light1_blue = 1;
        break;
        // red
        case 3:
            light1_red = 1;
            light1_green = 0;
            light1_blue = 0;
        break;
        // blue
        case 4:
            light1_red = 0;
            light1_green = 0;
            light1_blue = 1;
        break;
        // green
        case 5:
            light1_red = 0;
            light1_green = 1;
            light1_blue = 0;
        break;
    }
    glutPostRedisplay();
}


// sub menu to set the colour of light 2
void l2_sub_menu(GLint colour_option){
    switch (colour_option) {
        // off
        case 1:
            light2_red = 0;
            light2_green = 0;
            light2_blue = 0;
        break;
        // white
        case 2:
            light2_red = 1;
            light2_green = 1;
            light2_blue = 1;
        break;
        // red
        case 3:
            light2_red = 1;
            light2_green = 0;
            light2_blue = 0;
        break;
        // blue
        case 4:
            light2_red = 0;
            light2_green = 0;
            light2_blue = 1;
        break;
        // green
        case 5:
            light2_red = 0;
            light2_green = 1;
            light2_blue = 0;
        break;
    }
    glutPostRedisplay();
}


// sub menu to set the colour of light 3
void l3_sub_menu(GLint colour_option){
    switch (colour_option) {
        // off
        case 1:
            light3_red = 0;
            light3_green = 0;
            light3_blue = 0;
        break;
        // white
        case 2:
            light3_red = 1;
            light3_green = 1;
            light3_blue = 1;
        break;
        // red
        case 3:
            light3_red = 1;
            light3_green = 0;
            light3_blue = 0;
        break;
        // blue
        case 4:
            light3_red = 0;
            light3_green = 0;
            light3_blue = 1;
        break;
        // green
        case 5:
            light3_red = 0;
            light3_green = 1;
            light3_blue = 0;
        break;
    }
    glutPostRedisplay();
}


// sub menu to set the light properties of ambient, diffuse, and specular
void light_type_sub_menu(GLint light_type_option){
    switch (light_type_option) {
        // ambient
        case 1:
            light_properties[0] = GL_AMBIENT;
            light_properties[1] = NULL;
            light_properties[2] = NULL;
        break;
        // ambient, diffuse
        case 2:
            light_properties[0] = GL_AMBIENT;
            light_properties[1] = GL_DIFFUSE;
            light_properties[2] = NULL;
        break;
        // ambient, diffuse, specular
        case 3:
            light_properties[0] = GL_AMBIENT;
            light_properties[1] = GL_DIFFUSE;
            light_properties[2] = GL_SPECULAR;
            
        break;
    }
    glutPostRedisplay();
}


// sub menu to set the material for the sphere
void material_sub_menu(GLint material_option){
    switch (material_option) {
        // gold
        case 1:
            std::copy(gold_specular, gold_specular + 4, specular);
            std::copy(gold_diffuse, gold_diffuse + 4, diffuse);
            std::copy(gold_shininess, gold_shininess + 4, shininess);
            break;
        // silver
        case 2:
            std::copy(silver_specular, silver_specular + 4, specular);
            std::copy(silver_diffuse, silver_diffuse + 4, diffuse);
            std::copy(silver_shininess, silver_shininess + 4, shininess);
            break;
        // copper
        case 3:
            std::copy(copper_specular, copper_specular + 4, specular);
            std::copy(copper_diffuse, copper_diffuse + 4, diffuse);
            std::copy(copper_shininess, copper_shininess + 4, shininess);
        break;
    }
    glutPostRedisplay();
}


// render method sets the light properties given the
// current user-chosen configuration, and renders the sphere
// it also enables the 3 lights and sets their properties
void render() {
    
    // set colour to grey
    glColor3f(0.5, 0.5, 0.5);

    // set specular, diffuse, and shininess, and draw sphere
    glPushMatrix();
    
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
        
        //draw sphere
        glutSolidSphere(1.0, 64, 10);

    glPopMatrix();
    
    // enable lights
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    
    
    // set types and coordinate positions for lights
    // note all lights are set to local source (1.0)
    GLfloat light1_colour[] = { light1_red, light1_green, light1_blue, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    
    for (GLfloat element : light_properties){
        glLightfv(GL_LIGHT1, element, light1_colour);
    }
    
    GLfloat light2_colour[] = { light2_red, light2_green, light2_blue, 1.0 };
    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    
    for (GLfloat element : light_properties){
        glLightfv(GL_LIGHT2, element, light2_colour);
    }
    
    GLfloat light3_colour[] = { light3_red, light3_green, light3_blue, 1.0 };
    glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
    
    for (GLfloat element : light_properties){
        glLightfv(GL_LIGHT3, element, light3_colour);
    }
}


// display method
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

// creates menu system
void generate_menu_system(){
    
    // create menu system: main_menu has 5 submenus and 'Quit' option
    GLint l1 = glutCreateMenu(l1_sub_menu);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White Light", 2);
        glutAddMenuEntry("Red Light", 3);
        glutAddMenuEntry("Blue Light", 4);
        glutAddMenuEntry("Green Light", 5);

    GLint l2 = glutCreateMenu(l2_sub_menu);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White Light", 2);
        glutAddMenuEntry("Red Light", 3);
        glutAddMenuEntry("Blue Light", 4);
        glutAddMenuEntry("Green Light", 5);
    
    GLint l3 = glutCreateMenu(l3_sub_menu);
        glutAddMenuEntry("Off", 1);
        glutAddMenuEntry("White Light", 2);
        glutAddMenuEntry("Red Light", 3);
        glutAddMenuEntry("Blue Light", 4);
        glutAddMenuEntry("Green Light", 5);
    
    GLint light_type = glutCreateMenu(light_type_sub_menu);
        glutAddMenuEntry("Ambient only", 1);
        glutAddMenuEntry("Ambient and Diffuse", 2);
        glutAddMenuEntry("Ambient, Diffuse and Specular", 3);

    GLint material = glutCreateMenu(material_sub_menu);
        glutAddMenuEntry("Gold", 1);
        glutAddMenuEntry("Silver", 2);
        glutAddMenuEntry("Copper", 3);
    
    glutCreateMenu(main_menu);
        glutAddSubMenu("Light1", l1);
        glutAddSubMenu("Light2", l2);
        glutAddSubMenu("Light3", l3);
        glutAddSubMenu("Material Properties", material);
        glutAddSubMenu("Light Elements", light_type);

    glutAddMenuEntry("Quit", 2);
    
    // set menu system to be activated by right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// main method
int main(int argc, char **argv){

    glutInit (&argc, argv);
    
    // initialize display
    initDisplay(500, 500, "Teodor Ilie, 3564886 - Program 1: Lighting elements and surface materials");
    glutDisplayFunc( display );

    // generate the main menu system
    generate_menu_system();
    
    glutReshapeFunc( reshape );
    glutMainLoop();

}
