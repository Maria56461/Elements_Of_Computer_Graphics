#version 330

layout(location = 0) in vec3 v_position;
// pozitia in care cade lumina in spatiul obiect 
layout(location = 1) in vec3 v_normal;
// normala la suprafata in spatiul obiect 
layout(location = 2) in vec2 v_texture_coord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 world_position;
 // pozitia in care cade raza de lumina (calculata in spatiul lume)
out vec3 world_normal;
 // normala la suprafata in spatiul lume (este o directie, nu o pozitie)


void main() {

    world_position = vec3(Model * vec4(v_position, 1.0));
    world_normal = vec3(Model * vec4(v_normal, 0.0));
   
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
