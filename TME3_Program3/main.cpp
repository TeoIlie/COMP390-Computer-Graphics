/*  Athabasca University
    Comp390 - Introduction to Computer Graphics

    TME_3: Lighting and Surface Textures: Program 3

    @author: Teodor Ilie, 3564886
    @date: July 20, 2022

    Using the code fom TME2 Program 2, this program
    adds a background using a bitmap image called "side.bmp".
*/

#include <iostream>
#include "math.h"
#include "windows.h"
#include "gl/glut.h"

using namespace std;

typedef GLfloat list_3D[3];
// The local coordinates of the far-left-lower and near-right-upper corners of the body are
// {0,0,0}, and {1,1,1}, respectively.
list_3D square_coords[4] = { {0.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0} };

// The coordinates of the far-left and near-right corners of the pyramid are
// {-0.2, 1.0, -0.2} and {1.2, 1.0, 1.2}, respectively.
// The coordinate of the tip of the pyramid is {0.5, 1.5, 0.5}.

list_3D triangle_coords[3] = { {-0.2, 1.0, 1.2}, {1.2, 1.0, 1.2}, {0.5, 1.5, 0.5} };

// The far-left and near-right corners of the ground are at
// {-1.0, 0.0, -0.5} and {2.0, 0.0, 2.5}, respectively.
float bottom_coords[4][3] = { {-1.0, 0.0, 2.5}, {2.0, 0.0, 2.5}, {2.0, 0.0, -0.5}, {-1.0, 0.0, -0.5} };

// bitmap image variables
GLubyte* image;
GLubyte* l_texture;

RGBTRIPLE rgb;
GLuint texName;

BITMAPFILEHEADER fileheader;
BITMAPINFOHEADER infoheader;


// initialize the display
void initDisplay(int width, int height, std::string title) {

    // we must initialize with a request for a depth buffer and refresh buffer
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);

    const char* display_title = title.c_str();
    int window_handle = glutCreateWindow(display_title);
    glutSetWindow(window_handle);

    // set background colour
    glClearColor(0.2, 0.5, 0.8, 0.0);

    // enable depth-buffer visibility-detection routine
    // otherwise, houses are drawn overlapping in incorrect ways
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode sets mode to wire frame or solid
    // constant GL_FILL represents a fill polygon, which is what we need here
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


// render a single house
void render_house() {
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

    // all display lists until 'house' are only compiled, not executed, using GL_COMPILE

    // display list for a square
    glNewList(single_square, GL_COMPILE);
    // set colour to red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
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
    glBegin(GL_TRIANGLES);
    glVertex3fv(triangle_coords[2]);
    glVertex3fv(triangle_coords[1]);
    glVertex3fv(triangle_coords[0]);
    glEnd();
    glEndList();

    // display list for the bottom rectangle
    glNewList(bottom_ground, GL_COMPILE);
    // set colour to green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
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


// draw the grey ground
// The front-left and far-right coordinates of the ground (grey) are at
// {-8.0, -0.1, -8.0} and {8.0, -0.1, 8.0}, respectively.
void grey_ground() {
    //set colour to grey
    glColor3f(0.6, 0.6, 0.6);

    //GL_POLYGON is required instead of GL_LINE_LOOP for drawing fill polygons
    glBegin(GL_POLYGON);
    glVertex3f(-8.0, -0.1, 8.0);
    glVertex3f(8.0, -0.1, 8.0);
    glVertex3f(8.0, -0.1, -8.0);
    glVertex3f(-8.0, -0.1, -8.0);
    glEnd();
}


// function for initializing the image
void initialize_image() {

    // make the image

    int i, j = 0;
    FILE* l_file;
    string fn = "side.bmp";
    const char* filename = fn.c_str();

    // open image file, return if error
    fopen_s(&l_file, filename, "rb");
    if (l_file == NULL) return;

    // read file header and header info
    fread(&fileheader, sizeof(fileheader), 1, l_file);
    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    // allocate space for the image file
    l_texture = (GLubyte*)malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    // read the data
    j = 0;
    for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++) {
        fread(&rgb, sizeof(rgb), 1, l_file);
        l_texture[j + 0] = (GLubyte)rgb.rgbtRed; // Red component
        l_texture[j + 1] = (GLubyte)rgb.rgbtGreen; // Green component
        l_texture[j + 2] = (GLubyte)rgb.rgbtBlue; // Blue component
        l_texture[j + 3] = (GLubyte)255; // Alpha value
        j += 4; // Go to the next position
    }
    fclose(l_file); // Closes the file stream

    // designate pixel storage type
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // name the texture
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    // set parameters for magnification and wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // set the parameters for the 2D texture space
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        l_texture);

}


// function for drawing the backrgound textures using 'side.bmp'
void background() {
    // enable 2D textures
    glEnable(GL_TEXTURE_2D);

    // draw the two texture panels
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(-8.0, -0.1, -8.0);
    glTexCoord2d(0, 1); glVertex3f(-8.0, 16.0, -8.0);
    glTexCoord2d(1, 1); glVertex3f(8.0, 16.0, -8.0);
    glTexCoord2d(1, 0); glVertex3f(8.0, -0.1, -8.0);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(-8.0, -0.1, 8.0);
    glTexCoord2d(0, 1); glVertex3f(-8.0, 16.0, 8.0);
    glTexCoord2d(1, 1); glVertex3f(-8.0, 16.0, -8.0);
    glTexCoord2d(1, 0); glVertex3f(-8.0, -0.1, -8.0);
    glEnd();

    //disable 2D texture so that the houses can be drawn
    glDisable(GL_TEXTURE_2D);

}


// render method
void render() {

    // draw the background
    background();

    // draw the grey ground cover
    grey_ground();

    // middle house
    render_house();

    // right of middle
    glPushMatrix();
    glTranslatef(4, 0, 0);
    render_house();
    glPopMatrix();

    // left of middle
    glPushMatrix();
    glTranslatef(-4, 0, 0);
    render_house();
    glPopMatrix();

    // right of front
    glPushMatrix();
    glTranslatef(3, 0, 4);
    glScalef(2.0, 1.0, 1.0);
    render_house();
    glPopMatrix();

    // left of front
    glPushMatrix();
    glTranslatef(-4, 0, 4);
    glScalef(1.8, 1.0, 1.0);
    render_house();
    glPopMatrix();

    // right of back
    glPushMatrix();
    glTranslatef(5, 0, -5);
    glScalef(1.0, 2.0, 1.0);
    render_house();
    glPopMatrix();

    // middle of back
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glScalef(1.5, 1.0, 1.0);
    render_house();
    glPopMatrix();

    // left of back
    glPushMatrix();
    glTranslatef(-5, 0, -5);
    glRotatef(60, 0, 1, 0); //rotation matrix
    render_house();
    glPopMatrix();
}



// display method
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //the viewing position(reference point)
    gluLookAt(5, 4, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    render();
    glutSwapBuffers();
}


// reshape method
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);
    glMatrixMode(GL_MODELVIEW);
}


// main method
int main(int argc, char** argv) {
    // initialize glut
    glutInit(&argc, argv);

    // initialize display
    initDisplay(550, 550, "Teodor Ilie, 3564886 - Program 3: Loading textures");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    initialize_image();

    glutMainLoop();
}
