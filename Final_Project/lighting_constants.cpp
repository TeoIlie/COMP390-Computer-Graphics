/*  Athabasca University
    Comp390 - Introduction to Computer Graphics

    Final Project

    @author: Teodor Ilie, 3564886
    @date: July 29, 2022
 
    All material properties and lighting properties are stored in
    lighting_constants.hpp. This class implements the set_material
    function to choose a surface property for drawing done by
    schematics.cpp.
*/
#include "lighting_constants.hpp"
// sets the material paramaters based on the passed value
void set_material(int option) {
    switch (option) {
        // wood 1
        case 0:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood1_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wood1_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, wood1_shininess);
            break;
            
        // sail
        case 1:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sail_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sail_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, sail_shininess);
            break;
            
        // wood 2
        case 2:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wood2_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wood2_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, wood2_shininess);
            break;
            
        // cloud
        case 3:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cloud_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cloud_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cloud_shininess);
            break;
            
        // sand
        case 4:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sand_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sand_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, sand_shininess);
            break;
            
        // water
        case 5:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, water_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, water_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, water_shininess);
            break;
            
        // sun
        case 6:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, sun_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, sun_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emissive);
            
            break;
            
        // ray
        case 7:
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ray_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ray_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, ray_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ray_emissive);
            break;
            
        // silver metal
        case 8:
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, metal_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, metal_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, metal_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, metal_shininess);
            break;
            
        // red metal
        case 9:
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, red_shininess);
            break;

    }
    
    // set all but the sunlight and rays to non emissive
    if (option != 6 || option != 7)
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, non_emissive);
}
