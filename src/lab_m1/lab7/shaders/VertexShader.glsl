#version 330

layout(location = 0) in vec3 v_position;
// pozitia in care cade raza de lumina pe suprafata 
layout(location = 1) in vec3 v_normal;
// normala la suprafata in spatiul obiect 
layout(location = 2) in vec2 v_texture_coord;

uniform mat4 Model;
// matricea de modelare 
uniform mat4 View;
// matricea de vizualizare 
uniform mat4 Projection;
// matricea de proiectie 

// Uniforms for light properties
uniform vec3 light_position;
// coordonatele sursei de lumina
uniform vec3 eye_position;
// coordonatele observatorului 
uniform float material_kd;
// constanta de reflexie difuza a materialului
uniform float material_ks;
// constanta speculara de reflexie a materialului 
uniform int material_shininess;
// exponentul de reflexie speculara a materialului 
uniform vec3 object_color;
// culoarea suprafetei pe care cade lumina 

out vec3 color;


void main() {
    
    vec3 world_position = vec3(Model * vec4(v_position, 1));
    // pozitia in care cade raza de lumina (calculata in spatiul lume)
    vec3 N = normalize(vec3(Model * vec4(v_normal, 0)));
    // normala la suprafata in spatiul lume (este o directie, nu o pozitie)
    vec3 L = normalize(light_position - world_position);
    // vectorul directiei luminii 
    vec3 R = reflect(-L, N);
    // vectorul razei reflectate 
    vec3 V = normalize(eye_position - world_position);
    // vectorul directiei privirii observatorului 
    
    float ambient_light = 0.25;
    float diffuse_light = dot(N, L);
    // componenta difuza a intensitatii luminii reflectate 
    float specular_light = 0;

    if (diffuse_light > 0) {
    // daca sursa de lumina se afla de aceeasi parte cu suprafata 
        specular_light = max(0, dot(R, V));
        specular_light = pow(specular_light, material_shininess) * material_ks;
    }

    diffuse_light = max(0, diffuse_light) * material_kd;
   
    float d = distance(light_position, world_position);
    float atten = 1 / (0.2 + d * 0.1 + d * d * 0.05f);
    // calculul factorului de atenuare

    color = (ambient_light + atten * (specular_light + diffuse_light)) * object_color;

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
